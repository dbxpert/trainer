#ifndef EXECUTOR_TRAINER_ENGINE_SOLUTION_RUNNER_H_
#define EXECUTOR_TRAINER_ENGINE_SOLUTION_RUNNER_H_

#include "common.h"

class SolutionRunner {
 public:
  SolutionRunner() = default;
  ~SolutionRunner() = default;

  LocalTable Run(unsigned int problem_number);
  const long GetElapsedTime() const;

 private:
  long elapsed_ = 0;
};

#endif /* EXECUTOR_TRAINER_ENGINE_SOLUTION_RUNNER_H_ */