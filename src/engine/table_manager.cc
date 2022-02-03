#include "table_manager.h"

TableManager::TableManager() : shm_segment_(boost::interprocess::create_only, "TRAINER_SHM_KEY", DFLT_SHM_SIZE) {
  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    AllocateTableInSharedMemory(i);
  }
}

TableManager::~TableManager() {
  boost::interprocess::shared_memory_object::remove("TRAINER_SHM_KEY");
}

void TableManager::AllocateTableInSharedMemory(const std::size_t table_idx) {
  auto table_name = TPCH_TABLE_NAMES[table_idx].c_str();
  tables_[table_idx] = shm_segment_.construct<table_vector>(table_name)(shm_segment_.get_segment_manager());
  
  auto table = tables_[table_idx];
  auto col_cnt = TPCH_TABLE_COLUMN_COUNT[table_idx];
  for (decltype(col_cnt) i = 0; i < col_cnt; ++i) {
    table->emplace_back(shm_segment_.get_segment_manager());
  }
}

SharedTable &TableManager::GetTableReference(const std::size_t table_idx) const {
  return *tables_[table_idx];
}

SharedTable &TableManager::GetTableReference(const std::string &table_name) const {
  auto table_idx = TPCH_TABLE_NAME_TO_INDEX[table_name];
  return GetTableReference(table_idx);
}