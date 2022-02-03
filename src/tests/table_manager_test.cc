#include "gtest/gtest.h"
#include "engine/table_manager.h"
#include "engine/common.h"

TEST(TableManagerTest, construct_and_destruct) {
  auto table_manager = new TableManager();
  shared_memory shm_segment(boost::interprocess::open_only, "TRAINER_SHM_KEY");
  EXPECT_EQ(shm_segment.get_size(), TableManager::DFLT_SHM_SIZE);
  EXPECT_EQ(shm_segment.get_num_named_objects(), TPCH_TABLE_COUNT);
  
  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    auto table_name = TPCH_TABLE_NAMES[i].c_str();
    auto shm_obj = shm_segment.find<SharedTable>(table_name);
    EXPECT_NE(shm_obj.first, nullptr);
    EXPECT_EQ(shm_obj.second, 1);
  }

  delete table_manager;

  try {
    shared_memory shm_segment(boost::interprocess::open_only, "TRAINER_SHM_KEY");
  } catch (const std::exception &e) {
    auto what = std::string(e.what());
    EXPECT_EQ(what.compare("No such file or directory"), 0);
  }
}

TEST(TableManagerTest, get_table_reference_by_index) {
  TableManager table_manager;
  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    auto &table = table_manager.GetTableReference(i);
    EXPECT_EQ(table.size(), TPCH_TABLE_COLUMN_COUNT[i]);
  } 
}

TEST(TableManagerTest, get_table_reference_by_name) {
  TableManager table_manager;
  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    auto name = TPCH_TABLE_NAMES[i];
    auto index = TPCH_TABLE_NAME_TO_INDEX[name];
    auto &table = table_manager.GetTableReference(name);
    EXPECT_EQ(table.size(), TPCH_TABLE_COLUMN_COUNT[index]);
  } 
}