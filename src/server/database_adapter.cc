#include "database_adapter.h"

bool DatabaseAdapter::Execute(const char *sql,  SQLHDBC hdbc) {
  SQLRETURN rc;

  rc = SQLAllocStmt(hdbc, &hstmt_);
  if (rc != SQL_SUCCESS) 
    return false;

  rc = SQLExecDirect(hstmt_, (SQLCHAR *)sql, SQL_NTS);
  if (rc != SQL_SUCCESS) 
    return false;

  return true;
}

Table DatabaseAdapter::Fetch() {
  SQLRETURN rc;
  SQLSMALLINT col_cnt;
  const int batch_size = 1024;
  SQLUINTEGER row_cnt;
  
  rc = SQLNumResultCols(hstmt_, &col_cnt);

  if (rc != SQL_SUCCESS) 
    throw std::runtime_error("Database adapter error");

  SQLINTEGER col[col_cnt][batch_size];

  rc = SQLSetStmtAttr(hstmt_, SQL_ATTR_ROW_ARRAY_SIZE, INT2PTR(batch_size), 0);
 
  if (rc != SQL_SUCCESS) 
    throw std::runtime_error("Database adapter error"); 
 
  for (int i = 0; i < col_cnt; ++i) {
    rc = SQLBindCol(hstmt_, i + 1, SQL_INTEGER, &col[i], sizeof(SQLINTEGER), NULL);
    if (rc != SQL_SUCCESS) 
      throw std::runtime_error("Database adapter error"); 
  }

  std::vector<std::vector<int>> row_array;
  if (SQLExtendedFetch(hstmt_, SQL_FETCH_NEXT, 0, &row_cnt, NULL) != SQL_NO_DATA) {
    for (int r = 0; r < static_cast<int>(row_cnt); ++r) {
      std::vector<int> row;
      for (int i = 0; i < col_cnt; ++i) {
        row.push_back(col[i][r]);
      }
      row_array.push_back(row);
    }
  }
 
  return row_array;
}

