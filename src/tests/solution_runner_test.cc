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
  TableManager table_manager;
  SolutionRunner solution_runner;
  auto result = solution_runner.Run(GenerateRandomNumber());
  EXPECT_TRUE(result.empty());
}

TEST(SolutionRunnerTest, set_wrong_problem_number) {
  TableManager table_manager;
  SolutionRunner solution_runner;
  EXPECT_DEATH(
    auto result = solution_runner.Run(UINT32_MAX);,
    "No such problem"
  );
}
