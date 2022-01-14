#include "gtest/gtest.h"
#include "engine/solution_runner.h"
#include "engine/common.h"
#include <random>

static inline unsigned int GenerateRandomNumber() {
  std::random_device rd;
  std::mt19937 mersenne(rd());
  std::uniform_int_distribution<> dist(1, PROBLEM_COUNT);
  return dist(mersenne);
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
  auto result = solution_runner.Run(GenerateRandomNumber(), GenerateDummyInputTables());
  EXPECT_TRUE(result.empty());
}

TEST(SolutionRunnerTest, set_wrong_problem_number) {
  SolutionRunner solution_runner;
  EXPECT_DEATH(
    auto result = solution_runner.Run(UINT32_MAX, GenerateDummyInputTables());,
    "No such problem"
  );
}

