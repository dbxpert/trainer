#include "runner.h"
#include "sharer.h"
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <vector>

static inline int ParseProblemNumber(int argc, char **args);
static inline void RunSolution(int problem_number); 

int main(int argc, char **args) {
  auto problem_number = ParseProblemNumber(argc, args);

  try {
    RunSolution(problem_number);
  } catch (const std::exception &e) {
    return -1;
  }
  
  return 0;
}

static inline int ParseProblemNumber(int argc, char **args) {
  assert(argc == 2);
  return atoi(args[1]);
}

static inline void RunSolution(int problem_number) {
  Runner runner(problem_number);
 
  Sharer sharer;
  sharer.ShareResultTable(runner.GetResultTable());
  sharer.ShareElapsedTime(runner.GetElapsedTime());
}