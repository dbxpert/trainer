#ifndef EXECUTOR_TRAINER_ENGINE_H_
#define EXECUTOR_TRAINER_ENGINE_H_

#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include "common.h"
#include <string>
#include <memory>

class TableManager;
class SolutionRunner;
class TableLoader;
class ResultChecker;

class Engine {
 public:
  Engine();
  ~Engine();

  void PrepareTables(const SQLHDBC connection);
  void PrepareDebug(unsigned int problem_number);
  const std::string RunSolution(unsigned int problem_number);
  const std::string CheckResult(unsigned int problem_number);

 private:
  std::unique_ptr<shared_memory> shm_segment_;
  std::unique_ptr<TableManager> table_manager_;
  std::unique_ptr<SolutionRunner> solution_runner_;
  std::unique_ptr<TableLoader> table_loader_;
  std::unique_ptr<ResultChecker> result_checker_;
};

#endif /* EXECUTOR_TRAINER_ENGINE_H_ */