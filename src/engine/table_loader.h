#ifndef EXECUTOR_TRAINER_ENGINE_TABLE_LOADER_H_
#define EXECUTOR_TRAINER_ENGINE_TABLE_LOADER_H_

#include <vector>
#include "common.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"

class TableLoader {
  public:
    TableLoader();
    ~TableLoader() = default;

    void Load(const SQLHDBC connection);
    const std::vector<Table> &GetInputTables() const { return input_tables_; }

  private:
    std::vector<Table> input_tables_;
};

#endif /* EXECUTOR_TRAINER_ENGINE_TABLE_LOADER_H_ */