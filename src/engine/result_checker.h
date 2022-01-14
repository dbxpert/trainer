#ifndef EXECUTOR_TRAINER_ENGINE_RESULT_CHECKER_H_
#define EXECUTOR_TRAINER_ENGINE_RESULT_CHECKER_H_

#include "common.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include <vector>

class ResultChecker {
 public:
  ResultChecker() = default;
  ~ResultChecker() = default;

  void LoadAnswers(const SQLHDBC connection);
  bool Check(unsigned int problem_number, const Table &result);
 
 private:
  std::vector<Table> answers_;
};

#endif /* EXECUTOR_TRAINER_ENGINE_RESULT_CHECKER_H_ */