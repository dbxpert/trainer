#include "engine/result_checker.h"
#include "server/database_connector.h"
#include "engine/common.h"
#include "gtest/gtest.h"
#include <random>

TEST(ResultCheckerTest, load_answers) {
  ResultChecker result_checker;
  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");

  result_checker.LoadAnswers(connector.GetConnection());

  auto &answers = result_checker.GetAnswers();
  EXPECT_EQ(answers.size(), PROBLEM_COUNT);
}

TEST(ResultCheckerTest, check_with_answer) {
  ResultChecker result_checker;
  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");

  for (std::size_t i = 0; i < PROBLEM_COUNT; ++i) {
    auto &dummy_result = result_checker.GetAnswers()[i];
    EXPECT_TRUE(result_checker.Check(i + 1, dummy_result));
  }
}