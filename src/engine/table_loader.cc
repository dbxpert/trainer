#include <string>
#include <iostream>
#include "table_loader.h"
#include "database_adapter.h"

TableLoader::TableLoader() : input_tables_(TPCH_TABLE_COUNT) {}

static inline std::string GenerateFetchQuery(int table_idx) {
  std::string query("select * from ");
  return query + TPCH_TABLE_NAMES[table_idx] + ";";
}

void TableLoader::Load(const SQLHDBC connection) {
  DatabaseAdapter db_adapter;

  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    std::cout << "  " << "Loading " << TPCH_TABLE_NAMES[i] << "..." << std::endl; 
    db_adapter.SetSQL(GenerateFetchQuery(i));
    
    auto &dest = input_tables_[i];
    while (!db_adapter.FetchFinished()) {
      auto result = db_adapter.Load(connection);
      dest.insert(dest.begin(), result.begin(), result.end());
    } 
  }
}
