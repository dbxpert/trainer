#ifndef EXECUTOR_TRAINER_SERVER_SOLUTION_RUNNER_H_
#define EXECUTOR_TRAINER_SERVER_SOLUTION_RUNNER_H_

#include "table.h"
#include <array>
#include <functional>
#include <vector>

class SolutionRunner {
 public:
 SolutionRunner() = default;
  ~SolutionRunner() = default;

  static constexpr std::size_t PROBLEM_COUNT = 5;
  Table Run(unsigned int problem_number, const std::vector<Table> &input_tables);
};

#endif /* EXECUTOR_TRAINER_SERVER_SOLUTION_RUNNER_H_ */