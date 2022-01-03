#ifndef EXECUTOR_TRAINER_DATABASE_LOADER_H_
#define EXECUTOR_TRAINER_DATABASE_LODAER_H_

#include <string>
#include "common.h"
#include "database_adapter.h"
#include "database_connector.h"

class DatabaseLoader {
  public:
    DatabaseLoader(const DatabaseConnector &connector) : connector_(connector) {} 
    DatabaseLoader(const DatabaseLoader& other) = delete;
    DatabaseLoader& operator=(const DatabaseLoader& other) = delete;
    ~DatabaseLoader() = default;
    
    Table Load();
    void SetSql(std::string sql) { sql_ = sql; }
    
  private:
    DatabaseAdapter adapter_;
    const DatabaseConnector &connector_;
    std::string sql_;
};

#endif /* EXECUTOR_TRAINER_DATABASE_LOADER_H_ */
