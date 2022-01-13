#include "gtest/gtest.h"
#include "server/problem_loader.h"
#include "server/database_connector.h"
#include <random>

TEST(ProblemLoaderTest, load_problem) {
  ProblemLoader problem_loader;
  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");

  problem_loader.Load(connector.GetConnection(), 1);
  auto &input_tables = problem_loader.GetInputTables();

  EXPECT_EQ(input_tables.size(), TPCH_TABLE_COUNT);
}

TEST(ProblemLoaderTest, set_wrong_problem_number) {
  ProblemLoader problem_loader;
  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");
  EXPECT_DEATH(
    problem_loader.Load(connector.GetConnection(), UINT32_MAX);,
    "No such problem"
  );
}
