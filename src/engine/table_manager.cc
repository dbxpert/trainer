#include "table_manager.h"

TableManager::TableManager(shared_memory &shm_segment) 
    : shm_segment_(shm_segment) {
  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    AllocateTableInSharedMemory(i);
  }
}

TableManager::~TableManager() {
  for (auto ptr : tables_)
    shm_segment_.destroy_ptr(ptr);
}

void TableManager::AllocateTableInSharedMemory(const std::size_t table_idx) {
  auto table_name = TPCH_TABLE_NAMES[table_idx].c_str();

  auto allocator = shm_segment_.get_segment_manager();
  auto table = shm_segment_.construct<table_vector>(table_name)(allocator);

  auto col_cnt = TPCH_TABLE_COLUMN_COUNT[table_idx];
  for (decltype(col_cnt) i = 0; i < col_cnt; ++i) {
    table->emplace_back(allocator);
  }
  
  tables_[table_idx] = table;
}

SharedTable &TableManager::GetTableReference(const std::size_t table_idx) const {
  return *tables_[table_idx];
}

SharedTable &TableManager::GetTableReference(const std::string &table_name) const {
  auto table_idx = TPCH_TABLE_NAME_TO_INDEX[table_name];
  return GetTableReference(table_idx);
}