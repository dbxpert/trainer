#include "gtest/gtest.h"
#include "engine/table_loader.h"
#include "engine/table_manager.h"
#include "server/database_connector.h"

static constexpr std::size_t DFLT_SHM_SIZE = 65536 * 16;
TEST(TableLoaderTest, load_table) {
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
  auto shm_segment = shared_memory(boost::interprocess::create_only, "TRAINER_SHM_KEY", DFLT_SHM_SIZE);

  DatabaseConnector connector;
  connector.Connect("gtest_user", "gtest_user");

  auto table_manager = new TableManager(shm_segment);
  auto table_loader = new TableLoader();
  table_loader->Load(connector.GetConnection(), *table_manager);

  EXPECT_EQ(table_manager->GetTableReference("CUSTOMER")[0].size(), 1000);
  EXPECT_EQ(table_manager->GetTableReference("LINEITEM")[0].size(), 1000);
  EXPECT_EQ(table_manager->GetTableReference("NATION")[0].size(), 25);
  EXPECT_EQ(table_manager->GetTableReference("ORDERS")[0].size(), 1000);
  EXPECT_EQ(table_manager->GetTableReference("PART")[0].size(), 1000);
  EXPECT_EQ(table_manager->GetTableReference("PARTSUPP")[0].size(), 1000);
  EXPECT_EQ(table_manager->GetTableReference("REGION")[0].size(), 5);
  EXPECT_EQ(table_manager->GetTableReference("SUPPLIER")[0].size(), 1000);

  delete table_loader;
  delete table_manager;

  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
}
