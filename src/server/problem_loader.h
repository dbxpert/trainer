#ifndef EXECUTOR_TRAINER_PROBLEM_LOADER_H_
#define EXECUTOR_TRAINER_PROBLEM_LOADER_H_

#include <vector>
#include "table.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"

class ProblemLoader {
  public:
    ProblemLoader();
    ~ProblemLoader() = default;

    void Load(const SQLHDBC connection, unsigned int problem_number);
    const std::vector<Table> &GetInputTables() const { return input_tables_; }

  private:
    std::vector<bool> SearchProblemTable(const SQLHDBC connection, unsigned int problem_number);
    void LoadInputTables(const SQLHDBC connection, std::vector<bool> fetch_info);

    std::vector<Table> input_tables_;
};

#endif /* EXECUTOR_TRAINER_PROBLEM_LOADER_H_ */