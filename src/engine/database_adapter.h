#ifndef EXECUTOR_TRAINER_ENGINE_DATABASE_ADAPTER_H_
#define EXECUTOR_TRAINER_ENGINE_DATABASE_ADAPTER_H_

#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include "common.h"
#include <string>

class DatabaseAdapter final {
  public:
    DatabaseAdapter() = default;
    DatabaseAdapter(const DatabaseAdapter &) = delete;
    DatabaseAdapter &operator=(const DatabaseAdapter &) = delete;
    ~DatabaseAdapter() = default;

    void SetSQL(const std::string &sql);
    Table Load(const SQLHDBC connection);
    bool FetchFinished() const;

   private:
    bool Execute(const char *sql, SQLHDBC hdbc);
    Table Fetch();

    std::string sql_;
    SQLHSTMT hstmt_;
    bool fetch_finished_ = true;
};

#endif /* EXECUTOR_TRAINER_ENGINE_DATABASE_ADAPTER_H_ */