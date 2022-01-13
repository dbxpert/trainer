#include "gtest/gtest.h"
#include "server/solution_runner.h"
#include "server/table.h"
#include "server/test_result.h"
#include <random>

static inline unsigned int GenerateRandomNumber() {
  std::random_device rd;
  std::mt19937 mersenne(rd());
  std::uniform_int_distribution<> dist(1,10);
  return dist(mersenne);
}

TEST(SolutionRunnerTest, set_problem_number) {
  SolutionRunner solution_runner;
  EXPECT_NO_FATAL_FAILURE(
    solution_runner.SetProblemNumber(GenerateRandomNumber());
  );
}

TEST(SolutionRunnerTest, set_wrong_problem_number) {
  SolutionRunner solution_runner;
  EXPECT_DEATH(
    solution_runner.SetProblemNumber(UINT32_MAX);,
    "No such problem"
  );
}

static inline std::vector<Table> GenerateDummyInputTables() {
  std::vector<Table> input_tables(TPCH_TABLE_COUNT);
  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    auto &table = input_tables[i];
    table.insert(table.begin(), TPCH_TABLE_COLUMN_COUNT[i], std::vector<float>());
  }
  return input_tables;
}

TEST(SolutionRunnerTest, run_solution) {
  SolutionRunner solution_runner;
  solution_runner.SetProblemNumber(GenerateRandomNumber());
  auto result = solution_runner.Run(GenerateDummyInputTables());
  EXPECT_TRUE(result.empty());
}