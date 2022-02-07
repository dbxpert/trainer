#include "runner.h"
#include "solutions.h"
#include "table.h"
#include <array>
#include <chrono>
#include <vector>
#include <functional>

template <std::size_t N>
constexpr ResultTable RunSolution(shared_memory &) {
  assert(false && "Wrong problem number");
  return ResultTable();
}

template <>
ResultTable RunSolution<1>(shared_memory &shm_segment) {
  auto lineitem = GetObjectFromSharedMemory<Table>(shm_segment, "LINEITEM"); 
  return SolutionForProblem1(*lineitem);
}

template <>
ResultTable RunSolution<2>(shared_memory &shm_segment) {
  auto part = GetObjectFromSharedMemory<Table>(shm_segment, "PART"); 
  auto partsupp = GetObjectFromSharedMemory<Table>(shm_segment, "PARTSUPP");
  return SolutionForProblem2(*part, *partsupp);
}

template <>
ResultTable RunSolution<3>(shared_memory &shm_segment) {
  auto customer = GetObjectFromSharedMemory<Table>(shm_segment, "CUSTOMER");
  auto orders = GetObjectFromSharedMemory<Table>(shm_segment, "ORDERS");
  auto lineitem = GetObjectFromSharedMemory<Table>(shm_segment, "LINEITEM");
  return SolutionForProblem3(*customer, *orders, *lineitem);
}

template <>
ResultTable RunSolution<4>(shared_memory &shm_segment) {
  auto nation = GetObjectFromSharedMemory<Table>(shm_segment, "NATION");
  auto supplier = GetObjectFromSharedMemory<Table>(shm_segment, "SUPPLIER");
  return SolutionForProblem4(*nation, *supplier);
}

template <>
ResultTable RunSolution<5>(shared_memory &shm_segment) {
  auto lineitem = GetObjectFromSharedMemory<Table>(shm_segment, "LINEITEM");
  return SolutionForProblem5(*lineitem);
}

static constexpr std::size_t TOTAL_PROBLEM_COUNT = 5;
using solution_type = std::function<ResultTable(shared_memory &)>;
static const std::array<solution_type, TOTAL_PROBLEM_COUNT> solution_array = {
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

Runner::Runner(int problem_number) {
  shared_memory shm_segment(boost::interprocess::open_only, "TRAINER_SHM_KEY");
  Timestamp start = std::chrono::system_clock::now();
  result_table_ = std::move(solution_array[problem_number](shm_segment));
  elapsed_ = GetDuration(start).count(); 
}

const ResultTable &Runner::GetResultTable() const { return result_table_; }
const long Runner::GetElapsedTime() const { return elapsed_; }