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

static inline SharedTable *GetDummyTable(shared_memory &, const LocalTable &src);

TEST(ResultCheckerTest, check_with_answer) {
  ResultChecker result_checker;
  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");
  result_checker.LoadAnswers(connector.GetConnection());
  auto &answers = result_checker.GetAnswers();

  boost::interprocess::shared_memory_object::remove("DUMMY_SHM_KEY");
  shared_memory shm_segment(boost::interprocess::create_only, "DUMMY_SHM_KEY", 65536);

  for (std::size_t i = 0; i < PROBLEM_COUNT; ++i) {
    auto dummy_table = GetDummyTable(shm_segment, answers[i]);
    EXPECT_TRUE(result_checker.Check(*dummy_table, i + 1));
    shm_segment.destroy_ptr(dummy_table);
  }

  boost::interprocess::shared_memory_object::remove("DUMMY_SHM_KEY");
}

static inline SharedTable *GetDummyTable(shared_memory &shm_segment, const LocalTable &src) {
  auto dummy_table = shm_segment.construct<table_vector>("DUMMY")(shm_segment.get_segment_manager());

  for (auto column : src) {
    dummy_table->emplace_back(shm_segment.get_segment_manager());
    auto &last_col = dummy_table->back();
    last_col.insert(last_col.begin(), column.begin(), column.end());
  }

  return dummy_table;
}
