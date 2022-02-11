#include "engine.h"
#include "table_manager.h"
#include "solution_runner.h"
#include "table_loader.h"
#include "result_checker.h"
#include <stdexcept>
#include <climits>
#include <iostream>

/* Default shared memory size is 2G */
static constexpr std::size_t DFLT_SHM_SIZE = 2147483648UL;
static inline std::unique_ptr<shared_memory> GetSharedMemorySegment();
static inline const std::string SerializeResult(bool success, long elapsed);

Engine::Engine()
    : shm_segment_(GetSharedMemorySegment()), 
      table_manager_(std::make_unique<TableManager>(*shm_segment_.get())),
      solution_runner_(std::make_unique<SolutionRunner>(*shm_segment_.get())),
      table_loader_(std::make_unique<TableLoader>()),
      result_checker_(std::make_unique<ResultChecker>()) {}

static inline std::unique_ptr<shared_memory> GetSharedMemorySegment() {
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
  return std::make_unique<shared_memory>(boost::interprocess::create_only, "TRAINER_SHM_KEY", DFLT_SHM_SIZE);
}

Engine::~Engine() {
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
}

void Engine::PrepareTables(const SQLHDBC connection) {
  std::cout << "Loading Tables From Trainer DB..." << std::endl;
  table_loader_->Load(connection, *table_manager_);
  std::cout << "Loading Answers From Trainer DB..." << std::endl;
  result_checker_->LoadAnswers(connection);
  std::cout << '\n' << "Trainer server started up" << std::endl;
}

void Engine::PrepareDebug(unsigned int problem_number) {
  solution_runner_->AllocateColumnsForResultTable(problem_number);
}

const std::string Engine::RunSolution(unsigned int problem_number) {
  solution_runner_->Run(problem_number);
  return CheckResult(problem_number);
}

const std::string Engine::CheckResult(unsigned int problem_number) {
  auto &result_table = solution_runner_->GetResultTable();
  auto success = result_checker_->Check(result_table, problem_number);

  auto elapsed_time = solution_runner_->GetElapsedTime();
  return SerializeResult(success, elapsed_time);
}

static inline const std::string SerializeResult(bool success, long elapsed) {
  std::vector<unsigned char> byte_array;

  for (std::size_t i = 0; i < sizeof(decltype(elapsed)); ++i) {
    byte_array.push_back(elapsed & 0xFF);
    elapsed >>= CHAR_BIT;
  }
  byte_array.push_back(static_cast<unsigned char>(success));

  return std::string(byte_array.begin(), byte_array.end());
}