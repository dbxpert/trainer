#include "database_adapter.h"
#include <array>
#include <stdexcept>
#include <vector>

void DatabaseAdapter::SetSQL(const std::string &sql) {
  sql_ = sql;
  sql_executed_ = false;
}

LocalTable DatabaseAdapter::Load(const SQLHDBC connection) {
  if (!sql_executed_)
    Execute(connection);

  return Fetch();
}

static inline constexpr void *INT2PTR(int x) { return reinterpret_cast<void *>(static_cast<ptrdiff_t>(x)); }

template <typename Function, typename... Args>
static inline void CallCLIFunction(Function f, Args... args) {
  SQLRETURN rc = f(args...);

  if (rc != SQL_SUCCESS)
    throw std::runtime_error("Database adapter error");
}

void DatabaseAdapter::Execute(const SQLHDBC hdbc) {
  CallCLIFunction(SQLAllocStmt, hdbc, &hstmt_);
  CallCLIFunction(SQLExecDirect, hstmt_, (SQLCHAR *)sql_.c_str(), SQL_NTS);

  sql_executed_ = true;
  fetching_ = true;
}

static constexpr uint16_t ROW_ARRAY_SIZE = UINT16_MAX;
LocalTable DatabaseAdapter::Fetch() {
  if (!fetching_)
    return LocalTable();

  SQLSMALLINT col_cnt;
  CallCLIFunction(SQLNumResultCols, hstmt_, &col_cnt);
  CallCLIFunction(SQLSetStmtAttr, hstmt_, SQL_ATTR_ROW_ARRAY_SIZE, INT2PTR(ROW_ARRAY_SIZE), 0);

  SQLREAL col[col_cnt][ROW_ARRAY_SIZE];
  for (int i = 0; i < col_cnt; ++i) {
    CallCLIFunction(SQLBindCol, hstmt_, i + 1, SQL_REAL, &col[i], sizeof(SQLREAL), nullptr);
  }

  SQLUINTEGER row_cnt;
  if (SQLExtendedFetch(hstmt_, SQL_FETCH_NEXT, 0, &row_cnt, nullptr) != SQL_SUCCESS) {
    fetching_ = false;
    CallCLIFunction(SQLCloseCursor, hstmt_);
    return LocalTable();
  }

  LocalTable result_table;
  for (int col_num = 0; col_num < col_cnt; ++col_num) {
    std::vector<float> column;
    column.insert(column.begin(), &col[col_num][0], &col[col_num][row_cnt]);
    result_table.push_back(column);
  }

  return result_table;
}

bool DatabaseAdapter::FetchFinished() const { return sql_executed_ && !fetching_; }