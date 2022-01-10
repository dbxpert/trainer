#ifndef EXECUTOR_TRAINER_DATABASE_CONNECTOR_H_
#define EXECUTOR_TRAINER_DATABASE_CONNECTOR_H_

#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include <string>

class DatabaseConnector final {
  public:
    DatabaseConnector();
    ~DatabaseConnector(); 

    bool Connect(std::string user, std::string password);
    const bool IsConnected() const;
    const SQLHDBC GetConnection() const; 

  private:
    void GetUserInfo();
    bool Disconnect();

    SQLHENV henv_;
    SQLHDBC hdbc_;
    bool connected_;
};

#endif /* EXECUTOR_TRAINER_DATABASE_CONNECTOR_H_ */