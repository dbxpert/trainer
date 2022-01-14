#ifndef EXECUTOR_TRAINER_ENGINE_SOLUTION_RUNNER_H_
#define EXECUTOR_TRAINER_ENGINE_SOLUTION_RUNNER_H_

#include "common.h"
#include <array>
#include <functional>
#include <vector>

class SolutionRunner {
 public:
  SolutionRunner() = default;
  ~SolutionRunner() = default;

  Table Run(unsigned int problem_number, const std::vector<Table> &input_tables);
  const long GetElapsedTime() const;

 private:
  long elapsed_ = 0;
};

#endif /* EXECUTOR_TRAINER_ENGINE_SOLUTION_RUNNER_H_ */