#ifndef EXECUTOR_TRAINER_DATABASE_ADAPTER_H_
#define EXECUTOR_TRAINER_DATABASE_ADAPTER_H_

#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include "table.h"

class DatabaseAdapter final {
  public:
    DatabaseAdapter() = default;
    DatabaseAdapter(const DatabaseAdapter &) = delete;
    DatabaseAdapter &operator=(const DatabaseAdapter &) = delete;
    ~DatabaseAdapter() = default;

    bool Execute(const char *sql, SQLHDBC hdbc);
    bool FetchFinished() const;
    Table Fetch();

  private:
    SQLHSTMT hstmt_;
    bool fetch_finished_ = true;
};

#endif /* EXECUTOR_TRAINER_DATABASE_ADAPTER_H_ */