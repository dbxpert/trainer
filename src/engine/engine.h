#ifndef EXECUTOR_TRAINER_ENGINE_H_
#define EXECUTOR_TRAINER_ENGINE_H_

#include "table_loader.h"
#include "solution_runner.h"
#include "result_checker.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include <string>

class Engine {
 public:
  Engine() = default;
  ~Engine() = default;

  void Prepare(const SQLHDBC connection);
  const std::string Run(unsigned int problem_number);

 private:
  TableLoader problem_loader_;
  SolutionRunner solution_runner_;
  ResultChecker result_checker_;
};

#endif /* EXECUTOR_TRAINER_ENGINE_H_ */