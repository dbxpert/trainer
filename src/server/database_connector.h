#ifndef EXECUTOR_TRAINER_DATABASE_CONNECTOR_H_
#define EXECUTOR_TRAINER_DATABASE_CONNECTOR_H_

#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include <stdexcept>

class DatabaseConnector final {
  public:
    DatabaseConnector() = default;
    ~DatabaseConnector() = default;

    bool Connect() {
      SQLRETURN rc;
      rc = SQLAllocEnv2(&henv_, true);

      if (rc != SQL_SUCCESS) 
        return false;

      rc = SQLAllocConnect(henv_, &hdbc_);

      if (rc != SQL_SUCCESS) 
        return false;

      rc = SQLConnect(hdbc_, (SQLCHAR *)ds_name_, SQL_NTS, (SQLCHAR *)user_, SQL_NTS, 
                      (SQLCHAR *)passwd_, SQL_NTS);

      if (rc != SQL_SUCCESS && SQL_SUCCESS_WITH_INFO)
        return false;

      connected_ = true;
      return true;
    }

    bool Disconnect() {
      SQLRETURN rc;

      rc = SQLFreeConnect(hdbc_);

      if (rc != SQL_SUCCESS)
        return false;
  
      rc = SQLFreeEnv(henv_);
     
      if (rc != SQL_SUCCESS)
        return false;

      connected_ = false;
      return true;
    }


    const SQLHDBC GetConnection() const { 
      if (!connected_) {
        throw std::runtime_error("GetConnection is not available");
      }
      
      return hdbc_; 
    }

  private:
    SQLHENV henv_;
    SQLHDBC hdbc_;
    unsigned char ds_name_[20] = "tibero";
    unsigned char user_[10] = "trainer";
    unsigned char passwd_[11] = "trainer1-4";
    bool connected_;
};

#endif /* EXECUTOR_TRAINER_DATABASE_CONNECTOR_H_ */
