#ifndef EXECUTOR_TRAINER_DATABASE_LOADER_H_
#define EXECUTOR_TRAINER_DATABASE_LODAER_H_

#include <string>
#include "table.h"
#include "database_adapter.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"

class DatabaseLoader {
  public:
    DatabaseLoader() = default;
    ~DatabaseLoader() = default;
    
    Table Load(const SQLHDBC connection);
    void SetSql(std::string sql) { sql_ = sql; }
    
  private:
    DatabaseAdapter adapter_;
    std::string sql_;
};

#endif /* EXECUTOR_TRAINER_DATABASE_LOADER_H_ */
