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

static inline unsigned int GenerateRandomNumber() {
  std::random_device rd;
  std::mt19937 mersenne(rd());
  std::uniform_int_distribution<> dist(1, PROBLEM_COUNT);
  return dist(mersenne);
}

static inline Table GetDummyResult(unsigned int problem_number) {
  Table table;
  std::size_t col_cnt;
  switch (problem_number) {
    case 1:
      col_cnt = 8;
      break;
    case 2:
      col_cnt = 1;
      break;
    case 3:
      col_cnt = 1;
      break;
    case 4:
      col_cnt = 3;
      break;
    case 5:
      col_cnt = 2;
      break;
    default:
      assert(false);
  }

  table.reserve(col_cnt);
  for (std::size_t i = 0; i < table.capacity(); ++i)
    table[i].clear();

  return table;
}

TEST(ResultCheckerTest, check_with_answer) {
  ResultChecker result_checker;
  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");

  result_checker.LoadAnswers(connector.GetConnection());

  auto problem_number = GenerateRandomNumber();
  auto dummy_result = GetDummyResult(problem_number);
  EXPECT_TRUE(result_checker.Check(problem_number, dummy_result));
}