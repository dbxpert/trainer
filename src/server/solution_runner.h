#ifndef EXECUTOR_TRAINER_SERVER_SOLUTION_RUNNER_H_
#define EXECUTOR_TRAINER_SERVER_SOLUTION_RUNNER_H_

#include "table.h"
#include "test_result.h"
#include <vector>
#include <functional>

class SolutionRunner {
 public:
  SolutionRunner() = default;
  ~SolutionRunner() = default;

  void SetProblemNumber(unsigned int problem_number);
  Table Run(const std::vector<Table> &input_tables);

 private:
  using solution_type = std::function<Table(const std::vector<Table> &)>; 

  solution_type solution_;
  Table result_table_;
};

#endif /* EXECUTOR_TRAINER_SERVER_SOLUTION_RUNNER_H_ */