#include <string>
#include "table_loader.h"
#include "database_adapter.h"

static inline std::string GenerateFetchQuery(int table_idx); 
static inline void InsertIntoDestTable(SharedTable &dest, LocalTable &src, std::size_t col_cnt);

void TableLoader::Load(const SQLHDBC connection, const TableManager &table_manager) {
  DatabaseAdapter db_adapter;

  for (std::size_t i = 0; i < TPCH_TABLE_COUNT; ++i) {
    db_adapter.SetSQL(GenerateFetchQuery(i));

    auto &dest = table_manager.GetTableReference(i);
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

static inline void InsertIntoDestTable(SharedTable &dest, LocalTable &src, std::size_t col_cnt) {
  if (src.empty())
    return;

  for (std::size_t i = 0; i < col_cnt; ++i) {
    auto &dest_col = dest[i];
    auto &result_col = src[i];
    dest_col.insert(dest_col.begin(), result_col.begin(), result_col.end());
  }
}
