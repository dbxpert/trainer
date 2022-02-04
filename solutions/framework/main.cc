#include "runner.h"
#include <stdexcept>
#include <iostream>
#include <vector>

static inline int ParseProblemNumber(int argc, char **args) noexcept;
static inline void SendResult(const std::vector<std::vector<float>> &result, const long elapsed);

int main(int argc, char **args) {
  auto problem_number = ParseProblemNumber(argc, args);

  try {
    Runner runner(problem_number);
    SendResult(runner.GetResultTable(), runner.GetElapsedTime());
  } catch (const std::runtime_error &e) {
    std::cout << "Exception while running solution #" << problem_number << ": ";
    std::cout << e.what() << std::endl;
    return -1;
  }
  
  return 0;
}

static inline int ParseProblemNumber(int argc, char **args) noexcept {
  return 1;
}

static inline void SendResult(const std::vector<std::vector<float>> &result, const long elapsed) {
  return;
}
