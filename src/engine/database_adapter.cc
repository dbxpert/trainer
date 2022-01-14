#include "database_adapter.h"
#include <vector>
#include <array>
#include <stdexcept>

void DatabaseAdapter::SetSQL(const std::string &sql) { 
  sql_ = sql; 
}

Table DatabaseAdapter::Load(const SQLHDBC connection) {
  if (!Execute(sql_.c_str(), connection)) {
    std::runtime_error("Database adapter error");
  }  
  return Fetch();
}

static inline constexpr void *INT2PTR(int x) {
  return reinterpret_cast<void *>(static_cast<ptrdiff_t>(x));
}

template <typename Function, typename... Args>
static inline bool CallCLIFunction(Function f, Args... args) {
  SQLRETURN rc = f(args...);
  return rc == SQL_SUCCESS;
}

bool DatabaseAdapter::Execute(const char *sql,  SQLHDBC hdbc) {
  if (!fetch_finished_)
    return false;

  if (!CallCLIFunction(SQLAllocStmt, hdbc, &hstmt_))
    return false;

  if (!CallCLIFunction(SQLExecDirect, hstmt_, (SQLCHAR *)sql, SQL_NTS))
    return false;

  fetch_finished_ = false;
  return true;
}

static constexpr uint16_t ROW_ARRAY_SIZE = UINT16_MAX;
Table DatabaseAdapter::Fetch() {
  if (fetch_finished_)
    return Table();

  SQLSMALLINT col_cnt;
  if (!CallCLIFunction(SQLNumResultCols, hstmt_, &col_cnt))
    throw std::runtime_error("Database adapter error");

  if (!CallCLIFunction(SQLSetStmtAttr, hstmt_, SQL_ATTR_ROW_ARRAY_SIZE, INT2PTR(ROW_ARRAY_SIZE), 0))
    throw std::runtime_error("Database adapter error");

  SQLREAL col[col_cnt][ROW_ARRAY_SIZE];
  for (int i = 0; i < col_cnt; ++i) {
    if (!CallCLIFunction(SQLBindCol, hstmt_, i + 1, SQL_REAL, &col[i], sizeof(SQLREAL), nullptr))
      throw std::runtime_error("Database adapter error"); 
  }

  SQLUINTEGER row_cnt;
  if (!CallCLIFunction(SQLExtendedFetch, hstmt_, SQL_FETCH_NEXT, 0, &row_cnt, nullptr))
    return Table();

  fetch_finished_ = (row_cnt < ROW_ARRAY_SIZE);

  Table result_table;
  for (int col_num = 0; col_num < col_cnt; ++col_num) {
    std::vector<float> column(*col[col_num], col[col_num][row_cnt]);
    result_table.push_back(column);
  }

  return result_table;
}

bool DatabaseAdapter::FetchFinished() const {
  return fetch_finished_;
}