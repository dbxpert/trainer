#include "solution_runner.h"
#include "solutions/solutions.h"
#include <cassert>

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
  auto &orders = input_tables[TPCH_TABLE_NAME_TO_INDEX["ORDERS"]];
  auto &lineitem = input_tables[TPCH_TABLE_NAME_TO_INDEX["LINEITEM"]];
  return SolutionForProblem2(orders, lineitem);
}

template <>
Table RunSolution<3>(const std::vector<Table> &input_tables) {
  auto &customer = input_tables[TPCH_TABLE_NAME_TO_INDEX["CUSTOMER"]];
  auto &orders = input_tables[TPCH_TABLE_NAME_TO_INDEX["ORDERS"]];
  auto &lineitem = input_tables[TPCH_TABLE_NAME_TO_INDEX["LINEITEM"]];
  auto &supplier = input_tables[TPCH_TABLE_NAME_TO_INDEX["SUPPLIER"]];
  auto &nation = input_tables[TPCH_TABLE_NAME_TO_INDEX["NATION"]];
  auto &region = input_tables[TPCH_TABLE_NAME_TO_INDEX["REGION"]];
  return SolutionForProblem3(customer, orders, lineitem, supplier, nation, region);
}

template <>
Table RunSolution<4>(const std::vector<Table> &input_tables) {
  auto &customer = input_tables[TPCH_TABLE_NAME_TO_INDEX["CUSOTMER"]];
  auto &orders = input_tables[TPCH_TABLE_NAME_TO_INDEX["ORDERS"]];
  auto &lineitem = input_tables[TPCH_TABLE_NAME_TO_INDEX["LINEITEM"]];
  return SolutionForProblem4(customer, orders, lineitem);
}

template <>
Table RunSolution<5>(const std::vector<Table> &input_tables) {
  auto &orders = input_tables[TPCH_TABLE_NAME_TO_INDEX["ORDERS"]];
  auto &lineitem = input_tables[TPCH_TABLE_NAME_TO_INDEX["LINEITEM"]];
  return SolutionForProblem5(orders, lineitem);
}

using solution_type = std::function<Table(const std::vector<Table> &)>;
static const std::array<solution_type, SolutionRunner::PROBLEM_COUNT> solution_array = {
  RunSolution<1>,
  RunSolution<2>,
  RunSolution<3>,
  RunSolution<4>,
  RunSolution<5>
};

Table SolutionRunner::Run(unsigned int problem_number, const std::vector<Table> &input_tables) {
  assert(problem_number <= PROBLEM_COUNT && "No such problem");
  return solution_array[problem_number](input_tables);
}