#include "gtest/gtest.h"
#include "engine/table_loader.h"
#include "engine/table_manager.h"
#include "server/database_connector.h"

TEST(TableLoaderTest, load_table) {
  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");

  TableManager table_manager;
  TableLoader table_loader;
  table_loader.Load(connector.GetConnection(), table_manager);

  EXPECT_EQ(table_manager.GetTableReference("CUSTOMER")[0].size(), 1000);
  EXPECT_EQ(table_manager.GetTableReference("LINEITEM")[0].size(), 1000);
  EXPECT_EQ(table_manager.GetTableReference("NATION")[0].size(), 25);
  EXPECT_EQ(table_manager.GetTableReference("ORDERS")[0].size(), 1000);
  EXPECT_EQ(table_manager.GetTableReference("PART")[0].size(), 1000);
  EXPECT_EQ(table_manager.GetTableReference("PARTSUPP")[0].size(), 1000);
  EXPECT_EQ(table_manager.GetTableReference("REGION")[0].size(), 5);
  EXPECT_EQ(table_manager.GetTableReference("SUPPLIER")[0].size(), 1000);
}
