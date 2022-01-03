#ifndef EXECUTOR_TRAINER_PROBLEM_LOADER_H_
#define EXECUTOR_TRAINER_PROBLEM_LOADER_H_

#include <vector>
#include "common.h"
#include "database_connector.h"

class ProblemLoader {
  public:
    ProblemLoader() = default;
    ~ProblemLoader() = default;

    void Load(unsigned int problem_number);
    const std::vector<Table> &GetInputTables() const {
      return input_tables_;
    }

  private:
    void Connect();
    std::vector<bool> SearchProblemTable(unsigned int problem_number);
    void LoadInputTables(std::vector<bool> fetch_info);

    DatabaseConnector connector_;
    std::vector<Table> input_tables_;
};

#endif /* EXECUTOR_TRAINER_PROBLEM_LOADER_H_ */
