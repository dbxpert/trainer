#ifndef EXECUTOR_TRAINER_TEST_H_
#define EXECUTOR_TRAINER_TEST_H_

#include <functional>
#include <vector>
#include "table.h"
#include "test_result.h"
#include "problem_loader.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"

class Test {
 public:
  Test() = default;
  ~Test() = default;

  TestResult Run(const SQLHDBC connection, unsigned int problem_number);

 private:
  using solution_func_type = std::function<Table(std::vector<Table>)>;

  void Prepare(const SQLHDBC connection, unsigned int problem_number);
  long CallSolutionFunction(solution_func_type);

  ProblemLoader problem_loader_;

  std::vector<Table> result_tables_;
  std::function<Table(std::vector<Table>)> pace_maker_solution_;
  std::function<Table(std::vector<Table>)> user_solution_;
};

#endif /* EXECUTOR_TRAINER_TEST_H_ */
