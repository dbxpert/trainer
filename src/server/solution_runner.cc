#include "solution_runner.h"
#include <functional>
#include <cassert>

static inline Table RunSolution1(const std::vector<Table> &input_tables) {
  return Table();
}

static inline Table RunSolution2(const std::vector<Table> &input_tables) {
  return Table();
}

static inline Table RunSolution3(const std::vector<Table> &input_tables) {
  return Table();
}

static inline Table RunSolution4(const std::vector<Table> &input_tables) {
  return Table();
}

static inline Table RunSolution5(const std::vector<Table> &input_tables) {
  return Table();
}

static inline Table RunSolution6(const std::vector<Table> &input_tables) {
  return Table();
}

static inline Table RunSolution7(const std::vector<Table> &input_tables) {
  return Table();
}

static inline Table RunSolution8(const std::vector<Table> &input_tables) {
  return Table();
}

static inline Table RunSolution9(const std::vector<Table> &input_tables) {
  return Table();
}

static inline Table RunSolution10(const std::vector<Table> &input_tables) {
  return Table();
}

void SolutionRunner::SetProblemNumber(unsigned int problem_number) {
  switch (problem_number) {
    case 1:
      solution_ = RunSolution1;
      break;
    case 2:
      solution_ = RunSolution2;
      break;
    case 3:
      solution_ = RunSolution3;
      break;
    case 4:
      solution_ = RunSolution4;
      break;
    case 5:
      solution_ = RunSolution5;
      break;
    case 6:
      solution_ = RunSolution6;
      break;
    case 7:
      solution_ = RunSolution7;
      break;
    case 8:
      solution_ = RunSolution8;
      break;
    case 9:
      solution_ = RunSolution9;
      break;
    case 10:
      solution_ = RunSolution10;
      break;
    default:
      assert(false && "No such problem");
      break;
  }
}

Table SolutionRunner::Run(const std::vector<Table> &input_tables) {
  return solution_(input_tables);
}