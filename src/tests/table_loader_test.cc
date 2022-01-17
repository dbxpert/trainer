#include "gtest/gtest.h"
#include "engine/table_loader.h"
#include "server/database_connector.h"

TEST(TableLoaderTest, load_table) {
  TableLoader table_loader;
  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");

  table_loader.Load(connector.GetConnection());
  auto &input_tables = table_loader.GetInputTables();

  EXPECT_EQ(input_tables.size(), TPCH_TABLE_COUNT);
}
