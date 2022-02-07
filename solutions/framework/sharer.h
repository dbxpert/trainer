#ifndef EXECUTOR_TRAINER_SOLUTIONS_SHARER_H_
#define EXECUTOR_TRAINER_SOLUTIONS_SHARER_H_

#include <vector>

class Sharer {
 public:
  Sharer() = default;
  ~Sharer() = default;

  void ShareResultTable(const std::vector<std::vector<float>> &table);
  void ShareElapsedTime(const long elapsed_time);
};

#endif /* EXECUTOR_TRAINER_SOLUTIONS_SHARER_H_ */