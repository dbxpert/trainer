#include "gtest/gtest.h"
#include "engine/table_manager.h"
#include "engine/common.h"

static constexpr std::size_t DFLT_SHM_SIZE = 65536 * 16;
TEST(TableManagerTest, construct_and_destruct) {
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
  shared_memory shm_segment(boost::interprocess::create_only, "TRAINER_SHM_KEY", DFLT_SHM_SIZE);
  
  auto table_manager = new TableManager(shm_segment);
  EXPECT_EQ(shm_segment.get_num_named_objects(), TPCH_TABLE_COUNT);
  
  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    auto table_name = TPCH_TABLE_NAMES[i].c_str();
    auto shm_obj = shm_segment.find<SharedTable>(table_name);
    EXPECT_NE(shm_obj.first, nullptr);
    EXPECT_EQ(shm_obj.second, 1);
  }

  delete table_manager;
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
}

TEST(TableManagerTest, get_table_reference_by_index) {
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
  shared_memory shm_segment(boost::interprocess::create_only, "TRAINER_SHM_KEY", DFLT_SHM_SIZE);
 
  auto table_manager = new TableManager(shm_segment);
  
  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    auto &table = table_manager->GetTableReference(i);
    EXPECT_EQ(table.size(), TPCH_TABLE_COLUMN_COUNT[i]);
  } 
  
  delete table_manager;
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
}

TEST(TableManagerTest, get_table_reference_by_name) {
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
  shared_memory shm_segment(boost::interprocess::create_only, "TRAINER_SHM_KEY", DFLT_SHM_SIZE);
 
  auto table_manager = new TableManager(shm_segment);
  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    auto name = TPCH_TABLE_NAMES[i];
    auto index = TPCH_TABLE_NAME_TO_INDEX[name];
    auto &table = table_manager->GetTableReference(name);
    EXPECT_EQ(table.size(), TPCH_TABLE_COLUMN_COUNT[index]);
  } 

  delete table_manager;
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
}