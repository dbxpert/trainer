#include "database_adapter.h"
#include <vector>
#include <stdexcept>

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

  SQLINTEGER col[col_cnt][ROW_ARRAY_SIZE];
  if (!CallCLIFunction(SQLSetStmtAttr, hstmt_, SQL_ATTR_ROW_ARRAY_SIZE, INT2PTR(ROW_ARRAY_SIZE), 0))
    throw std::runtime_error("Database adapter error");

  for (int i = 0; i < col_cnt; ++i) {
    if (!CallCLIFunction(SQLBindCol, hstmt_, i + 1, SQL_INTEGER, &col[i], sizeof(SQLINTEGER), nullptr))
      throw std::runtime_error("Database adapter error"); 
  }

  SQLUINTEGER row_cnt;
  if (!CallCLIFunction(SQLExtendedFetch, hstmt_, SQL_FETCH_NEXT, 0, &row_cnt, nullptr))
    return Table();

  fetch_finished_ = (row_cnt < ROW_ARRAY_SIZE);

  Table result_table;
  for (int row_num = 0; row_num < static_cast<int>(row_cnt); ++row_num) {
    std::vector<int> row;
    for (int col_num = 0; col_num < col_cnt; ++col_num) {
      row.push_back(col[col_num][row_num]);
    }
    result_table.push_back(row);
  }

  return result_table;
}

bool DatabaseAdapter::FetchFinished() const {
  return fetch_finished_;
}