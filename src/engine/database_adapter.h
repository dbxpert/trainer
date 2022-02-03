#ifndef EXECUTOR_TRAINER_ENGINE_DATABASE_ADAPTER_H_
#define EXECUTOR_TRAINER_ENGINE_DATABASE_ADAPTER_H_

#include "common.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include <string>

class DatabaseAdapter final {
 public:
  DatabaseAdapter() = default;
  DatabaseAdapter(const DatabaseAdapter &) = delete;
  DatabaseAdapter &operator=(const DatabaseAdapter &) = delete;
  ~DatabaseAdapter() = default;

  void SetSQL(const std::string &sql);
  LocalTable Load(const SQLHDBC connection);
  bool FetchFinished() const;

 private:
  void Execute(const SQLHDBC hdbc);
  LocalTable Fetch();

  std::string sql_;
  SQLHSTMT hstmt_;
  bool sql_executed_ = false;
  bool fetching_ = false;
};

#endif /* EXECUTOR_TRAINER_ENGINE_DATABASE_ADAPTER_H_ */