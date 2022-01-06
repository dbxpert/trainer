#include "server/database_adapter.h"
#include "server/database_connector.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(DatabaseAdapterTest, execute_sql) {
  DatabaseConnector connector("gtest_user", "gtest_user");
  DatabaseAdapter adapter;
  EXPECT_TRUE(adapter.Execute("SELECT * FROM DUAL;", connector.GetConnection()));
}

TEST(DatabaseAdapterTest, execute_and_fetch_data) {
  DatabaseConnector connector("gtest_user", "gtest_user");
  DatabaseAdapter adapter;

  int row_cnt = 0;
  if (adapter.Execute("SELECT * FROM UNIT_TEST_TABLE;", connector.GetConnection())) {
    while (!adapter.FetchFinished()) {
      auto result = adapter.Fetch();
      row_cnt += result.size();
    }
  }

  int actual_count = 0;
  if (adapter.Execute("SELECT COUNT(*) FROM UNIT_TEST_TABLE;", connector.GetConnection())) {
    auto result = adapter.Fetch();
    actual_count = result[0][0];
  }
  EXPECT_EQ(row_cnt, actual_count);
}