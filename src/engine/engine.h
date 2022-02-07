#ifndef EXECUTOR_TRAINER_ENGINE_H_
#define EXECUTOR_TRAINER_ENGINE_H_

#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include "result_checker.h"
#include "solution_runner.h"
#include "table_loader.h"
#include "table_manager.h"
#include "common.h"
#include <string>
#include <memory>

class Engine {
 public:
  Engine();
  ~Engine();

  void Prepare(const SQLHDBC connection);
  const std::string Run(unsigned int problem_number);

 private:
  std::unique_ptr<shared_memory> shm_segment_;
  
  TableManager table_manager_;
  SolutionRunner solution_runner_;
  TableLoader table_loader_;
  ResultChecker result_checker_;
};

#endif /* EXECUTOR_TRAINER_ENGINE_H_ */