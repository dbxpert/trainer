#include "gtest/gtest.h"
#include "engine/solution_runner.h"
#include "engine/common.h"
#include "engine/table_manager.h"
#include <random>

static inline unsigned int GenerateRandomNumber() {
  std::random_device rd;
  std::mt19937 mersenne(rd());
  std::uniform_int_distribution<> dist(1, PROBLEM_COUNT);
  return dist(mersenne);
}

TEST(SolutionRunnerTest, run_solution) {
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
  auto shm_segment = shared_memory(boost::interprocess::create_only, "TRAINER_SHM_KEY", 65536);

  auto table_manager = new TableManager(shm_segment);
  auto solution_runner = new SolutionRunner(shm_segment);
  auto problem_number = GenerateRandomNumber(); 

  try {
    solution_runner->Run(problem_number);
  } catch (const std::runtime_error &e) {
    /* solution이 작성되지 않은 상태에서는 solution_runner가 error를 뱉는다 */
    std::string what(e.what());
    EXPECT_EQ(what.compare("Unexpected error occurred while running solution"), 0);
  }
  
  delete solution_runner;
  delete table_manager;

  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
}

TEST(SolutionRunnerTest, set_wrong_problem_number) {
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
  auto shm_segment = shared_memory(boost::interprocess::create_only, "TRAINER_SHM_KEY", 65536);

  auto table_manager = new TableManager(shm_segment);
  auto solution_runner = new SolutionRunner(shm_segment);

  EXPECT_DEATH(
    solution_runner->Run(UINT32_MAX);, "No such problem"
  );

  delete solution_runner;
  delete table_manager;

  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
}
