#include "solution_runner.h"
#include "solutions/solutions.h"
#include <cassert>
#include <chrono>

template <std::size_t N>
constexpr Table RunSolution(const std::vector<Table> &) {
  assert(false && "Wrong problem number");
  return Table();
}

template <>
Table RunSolution<1>(const std::vector<Table> &input_tables) {
  auto &lineitem = input_tables[TPCH_TABLE_NAME_TO_INDEX["LINEITEM"]];
  return SolutionForProblem1(lineitem);
}

template <>
Table RunSolution<2>(const std::vector<Table> &input_tables) {
  auto &part = input_tables[TPCH_TABLE_NAME_TO_INDEX["PART"]];
  auto &partsupp = input_tables[TPCH_TABLE_NAME_TO_INDEX["PARTSUPP"]];
  return SolutionForProblem2(part, partsupp);
}

template <>
Table RunSolution<3>(const std::vector<Table> &input_tables) {
  auto &customer = input_tables[TPCH_TABLE_NAME_TO_INDEX["CUSTOMER"]];
  auto &orders = input_tables[TPCH_TABLE_NAME_TO_INDEX["ORDERS"]];
  auto &lineitem = input_tables[TPCH_TABLE_NAME_TO_INDEX["LINEITEM"]];
  return SolutionForProblem3(customer, orders, lineitem);
}

template <>
Table RunSolution<4>(const std::vector<Table> &input_tables) {
  auto &nation = input_tables[TPCH_TABLE_NAME_TO_INDEX["NATION"]];
  auto &supplier = input_tables[TPCH_TABLE_NAME_TO_INDEX["SUPPLIER"]];
  return SolutionForProblem4(nation, supplier);
}

template <>
Table RunSolution<5>(const std::vector<Table> &input_tables) {
  auto &lineitem = input_tables[TPCH_TABLE_NAME_TO_INDEX["LINEITEM"]];
  return SolutionForProblem5(lineitem);
}

using solution_type = std::function<Table(const std::vector<Table> &)>;
static const std::array<solution_type, PROBLEM_COUNT> solution_array = {
  RunSolution<1>,
  RunSolution<2>,
  RunSolution<3>,
  RunSolution<4>,
  RunSolution<5>
};

using Timestamp = std::chrono::system_clock::time_point;
using Duration = std::chrono::nanoseconds;

static inline Duration GetDuration(Timestamp start) {
  return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now() - start);
}

Table SolutionRunner::Run(unsigned int problem_number, const std::vector<Table> &input_tables) {
  assert(problem_number <= PROBLEM_COUNT && "No such problem");

  auto solution_idx = problem_number - 1;
  Timestamp start = std::chrono::system_clock::now();
  auto result = solution_array[solution_idx](input_tables);
  elapsed_ = GetDuration(start).count();

  return result;
}

const long SolutionRunner::GetElapsedTime() const {
  return elapsed_;
}