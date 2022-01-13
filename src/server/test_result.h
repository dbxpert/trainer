#ifndef EXECUTOR_TRAINER_TEST_RESULT_H_
#define EXECUTOR_TRAINER_TEST_RESULT_H_

#include <vector>

struct TestResult {
  long user_elapse_time;
  long pace_maker_elapse_time;
  bool success;
};

#endif /* EXECUTOR_TRAINER_TEST_RESULT_H_ */