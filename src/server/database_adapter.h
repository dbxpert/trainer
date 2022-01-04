#ifndef EXECUTOR_TRAINER_DATABASE_ADAPTER_H_
#define EXECUTOR_TRAINER_DATABASE_ADAPTER_H_

#include <iostream>
#include <vector>
#include "../include/sqlcli.h"
#include "../include/sqlcli_ext.h"
#include "table.h"

#define INT2PTR(x)      ((void *) ((ptrdiff_t) (x))) 

class DatabaseAdapter final {
  public:
    DatabaseAdapter() = default;
    DatabaseAdapter(const DatabaseAdapter &) = delete;
    DatabaseAdapter &operator=(const DatabaseAdapter &) = delete;
    ~DatabaseAdapter() = default;

    bool Execute(const char *sql, SQLHDBC hdbc);
    Table Fetch();

  private:
    SQLHSTMT hstmt_;
};

#endif /* EXECUTOR_TRAINER_DATABASE_ADAPTER_H_ */
