#include "solution_runner.h"
#include "common.h"
#include <cassert>
#include <cstdlib>

static inline void ExecuteSolutionRunner(unsigned int problem_number);

SolutionRunner::SolutionRunner(shared_memory &shm_segment) 
    : shm_segment_(shm_segment) {
  AllocateResultTableInSharedMemory();
  AllocateElapsedTimeInSharedMemory();
}

SolutionRunner::~SolutionRunner() {
  shm_segment_.destroy_ptr(result_table_);
  shm_segment_.destroy_ptr(elapsed_time_);
}

void SolutionRunner::AllocateResultTableInSharedMemory() {
  auto allocator = shm_segment_.get_segment_manager(); 
  result_table_ = shm_segment_.construct<table_vector>("RESULT_TABLE")(allocator);
}

void SolutionRunner::AllocateElapsedTimeInSharedMemory() {
  elapsed_time_ = shm_segment_.construct<long>("ELAPSED_TIME")(0);
}

void SolutionRunner::Run(unsigned int problem_number) {
  assert(problem_number <= PROBLEM_COUNT && "No such problem");
  AllocateColumnsForResultTable(problem_number);
  ExecuteSolutionRunner(problem_number);
}

void SolutionRunner::AllocateColumnsForResultTable(unsigned int problem_number) {
  auto column_count = COLUMN_COUNT_FOR_ANSWERS[problem_number - 1];
  for (std::size_t i = 0; i < column_count; ++i)
    result_table_->emplace_back(shm_segment_.get_segment_manager());
}

static inline void ExecuteSolutionRunner(unsigned int problem_number) {
  auto sol_runner_path = std::string(std::getenv("TRAINER_HOME")) + "/bin/solution_runner";
  auto problem_num_to_str = std::to_string(problem_number);
  auto command = sol_runner_path + " " + problem_num_to_str;
  
  auto return_code = system(command.c_str());

  if (return_code != 0)
    throw std::runtime_error("Unexpected error occurred while running solution");
}

void SolutionRunner::Debug(unsigned int problem_number) {
  auto sol_runner_path = std::string(std::getenv("TRAINER_HOME")) + "/bin/solution_runner";
  auto problem_num_to_str = std::to_string(problem_number);
  auto command = "cgdb --args " + sol_runner_path + " " + problem_num_to_str;
  
  auto return_code = system(command.c_str());

  if (return_code != 0)
    throw std::runtime_error("Unexpected error occurred while running solution");
}

const SharedTable &SolutionRunner::GetResultTable() const {
  return *result_table_;
}

const float SolutionRunner::GetElapsedTime() const {
  return *elapsed_time_;
}
