#include "solution_runner.h"
#include <cassert>

LocalTable SolutionRunner::Run(unsigned int problem_number) {
  assert(problem_number <= PROBLEM_COUNT && "No such problem");
  return LocalTable();
}

const long SolutionRunner::GetElapsedTime() const {
  return elapsed_;
}