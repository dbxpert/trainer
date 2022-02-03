#ifndef EXECUTOR_TRAINER_ENGINE_H_
#define EXECUTOR_TRAINER_ENGINE_H_

#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include "result_checker.h"
#include "solution_runner.h"
#include "table_loader.h"
#include "table_manager.h"
#include <string>

class Engine {
 public:
  Engine() = default;
  ~Engine() = default;

  void Prepare(const SQLHDBC connection);
  const std::string Run(unsigned int problem_number);

 private:
  TableManager table_manager_;
  TableLoader problem_loader_;
  SolutionRunner solution_runner_;
  ResultChecker result_checker_;
};

#endif /* EXECUTOR_TRAINER_ENGINE_H_ */