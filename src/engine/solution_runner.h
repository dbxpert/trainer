#ifndef EXECUTOR_TRAINER_ENGINE_SOLUTION_RUNNER_H_
#define EXECUTOR_TRAINER_ENGINE_SOLUTION_RUNNER_H_

#include "common.h"

class SolutionRunner {
 public:
  SolutionRunner(shared_memory &);
  ~SolutionRunner();

  void Run(unsigned int problem_number);

  const SharedTable &GetResultTable() const;
  const float GetElapsedTime() const;

 private:
  void AllocateResultTableInSharedMemory();
  void AllocateElapsedTimeInSharedMemory();
  void AllocateColumnsForResultTable(unsigned int problem_number);

  shared_memory &shm_segment_;
  SharedTable *result_table_;
  long *elapsed_time_;
};

#endif /* EXECUTOR_TRAINER_ENGINE_SOLUTION_RUNNER_H_ */