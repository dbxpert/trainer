#ifndef EXECUTOR_TRAINER_ENGINE_RESULT_CHECKER_H_
#define EXECUTOR_TRAINER_ENGINE_RESULT_CHECKER_H_

#include "common.h"
#include "include/sqlcli.h"
#include "include/sqlcli_ext.h"
#include <vector>
#include <string>

class ResultChecker {
 public:
  ResultChecker();
  ~ResultChecker() = default;

  void LoadAnswers(const SQLHDBC connection);

  const std::vector<LocalTable> &GetAnswers() const {
    return answers_;
  }

  const std::string GetComment() const { 
    return comment_; 
  }

  bool Check(const SharedTable &, unsigned int problem_number);

 private:
  std::vector<LocalTable> answers_;
  std::string comment_;
};

#endif /* EXECUTOR_TRAINER_ENGINE_RESULT_CHECKER_H_ */
