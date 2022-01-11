#include <algorithm>
#include <stdexcept>
#include <chrono>
#include "test.h"

static inline bool CheckResult(Table result, Table answer) {
  if (result.size() != answer.size())
    return false;

  std::sort(result.begin(), result.end());
  std::sort(answer.begin(), answer.end());

  return std::equal(result.begin(), result.end(), answer.begin(),
  [](const std::vector<float> &x, const std::vector<float> &y){
    return x[0] == y[0];
  });
}

TestResult Test::Run(const SQLHDBC connection, unsigned int problem_number) {
  Prepare(connection, problem_number);

  auto user_elapsed = CallSolutionFunction(user_solution_);
  auto pace_maker_elapsed = CallSolutionFunction(pace_maker_solution_);
  auto correct = CheckResult(result_tables_[0], result_tables_[1]);
  
  return TestResult{user_elapsed, pace_maker_elapsed, correct};
}

void Test::Prepare(const SQLHDBC connection, unsigned int problem_number) {
  problem_loader_.Load(connection, problem_number);
  
  std::vector<solution_func_type> pace_maker_solutions = {};
  std::vector<solution_func_type> user_solutions = {};
  auto solution_idx = problem_number - 1;

  pace_maker_solution_ = pace_maker_solutions[solution_idx];
  user_solution_ = user_solutions[solution_idx];
}

using Timestamp = std::chrono::system_clock::time_point;
using Duration = std::chrono::nanoseconds;

static inline Duration GetDuration(Timestamp start) {
  return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now() - start);
}

long Test::CallSolutionFunction(Test::solution_func_type function) {
  Timestamp start = std::chrono::system_clock::now();
  auto result = pace_maker_solution_(problem_loader_.GetInputTables());
  Duration elapsed = GetDuration(start);

  result_tables_.push_back(result);

  return elapsed.count(); 
}
