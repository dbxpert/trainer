#ifndef EXECUTOR_TRAINER_SOLUTIONS_RUNNER_H_
#define EXECUTOR_TRAINER_SOLUTIONS_RUNNER_H_

#include <vector>

class Runner {
 public:
  Runner(int problem_number);
  ~Runner() = default;

  const std::vector<std::vector<float>> &GetResultTable() const;
  const long GetElapsedTime() const;

 private:
  std::vector<std::vector<float>> result_table_;
  long elapsed_;
};

#endif /* EXECUTOR_TRAINER_SOLUTIONS_RUNNER_H_ */
