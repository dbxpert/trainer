#include <string>
#include <iostream>
#include "table_loader.h"
#include "database_adapter.h"

static inline std::string GenerateFetchQuery(int table_idx); 
static inline void InitializeDestTable(Table &dest, std::size_t table_idx);
static inline void InsertIntoDestTable(Table &dest, Table &src, std::size_t col_cnt);

TableLoader::TableLoader() : input_tables_(TPCH_TABLE_COUNT) {}

void TableLoader::Load(const SQLHDBC connection) {
  DatabaseAdapter db_adapter;

  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    std::cout << "  " << "Loading " << TPCH_TABLE_NAMES[i] << "..." << std::endl; 
    db_adapter.SetSQL(GenerateFetchQuery(i));

    auto &dest = input_tables_[i];
    InitializeDestTable(dest, i);
    while (!db_adapter.FetchFinished()) {
      auto result = db_adapter.Load(connection);
      InsertIntoDestTable(dest, result, TPCH_TABLE_COLUMN_COUNT[i]);
    } 
  }
}

static inline std::string GenerateFetchQuery(int table_idx) {
  std::string query("select * from ");
  return query + TPCH_TABLE_NAMES[table_idx] + ";";
}

static inline void InitializeDestTable(Table &dest, std::size_t table_idx) {
    auto column_count = TPCH_TABLE_COLUMN_COUNT[table_idx];
    for (std::size_t i = 0; i < column_count; ++i)
      dest.emplace_back();
}

static inline void InsertIntoDestTable(Table &dest, Table &src, std::size_t col_cnt) {
  if (src.empty())
    return;

  for (std::size_t i = 0; i < col_cnt; ++i) {
    auto &dest_col = dest[i];
    auto &result_col = src[i];
    dest_col.insert(dest_col.begin(), result_col.begin(), result_col.end());
  }
}
