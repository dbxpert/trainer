#include "engine/database_adapter.h"
#include "server/database_connector.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(DatabaseAdapterTest, execute_sql) {
  DatabaseConnector connector;
  DatabaseAdapter adapter;
  
  connector.Connect("gtest_user", "gtest_user");
  adapter.SetSQL("SELECT 1 FROM DUAL;");

  Table result;
  while (!adapter.FetchFinished()) {
    auto ret = adapter.Load(connector.GetConnection());
    result.insert(result.begin(), ret.begin(), ret.end());
  }

  EXPECT_EQ(result.size(), 1);
}

TEST(DatabaseAdapterTest, execute_and_fetch_data) {
  DatabaseConnector connector;
  DatabaseAdapter adapter;
  
  connector.Connect("gtest_user", "gtest_user");
  adapter.SetSQL("SELECT * FROM UNIT_TEST_TABLE;");

  std::size_t row_cnt = 0;
  while (!adapter.FetchFinished()) {
    auto result = adapter.Load(connector.GetConnection());
    if (!result.empty())
      row_cnt += result[0].size();
  }
  
  adapter.SetSQL("SELECT COUNT(*) FROM UNIT_TEST_TABLE;");
  float actual_count = 0;
  while (!adapter.FetchFinished()) {
    auto result = adapter.Load(connector.GetConnection());
    if (!result.empty())
      actual_count += result[0][0];
  }

  EXPECT_EQ(row_cnt, static_cast<std::size_t>(actual_count));
}