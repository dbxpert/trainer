#ifndef EXECUTOR_TRAINER_ENGINE_TABLE_LOADER_H_
#define EXECUTOR_TRAINER_ENGINE_TABLE_LOADER_H_

#include "common.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include "table_manager.h"

class TableLoader {
 public:
  TableLoader() = default;
  ~TableLoader() = default;

  void Load(const SQLHDBC connection, const TableManager &);
};

#endif /* EXECUTOR_TRAINER_ENGINE_TABLE_LOADER_H_ */