#ifndef EXECUTOR_TRAINER_PROBLEM_LOADER_H_
#define EXECUTOR_TRAINER_PROBLEM_LOADER_H_

#include <vector>
#include "table.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"

class ProblemLoader {
  public:
    ProblemLoader() = default;
    ~ProblemLoader() = default;

    void Load(const SQLHDBC connection, unsigned int problem_number);
    const std::vector<Table> &GetInputTables() const { return input_tables_; }

    static constexpr unsigned int MINIMUM_NUMBER = 1;
    static constexpr unsigned int MAXIMUM_NUMBER = 10;
    static constexpr unsigned int TABLE_COUNT = 8;

  private:
    std::vector<bool> SearchProblemTable(const SQLHDBC connection, unsigned int problem_number);
    void LoadInputTables(const SQLHDBC connection, std::vector<bool> fetch_info);

    std::vector<Table> input_tables_;
};

#endif /* EXECUTOR_TRAINER_PROBLEM_LOADER_H_ */
