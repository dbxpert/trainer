#ifndef EXECUTOR_TRAINER_SOLUTIONS_H_
#define EXECUTOR_TRAINER_SOLUTIONS_H_

#include "framework/table.h"
#include <vector>

using ResultTable = std::vector<std::vector<float>>;

ResultTable SolutionForProblem1(const Table &lineitem);

ResultTable SolutionForProblem2(const Table &part, const Table &partsupp);

ResultTable SolutionForProblem3(const Table &customer, const Table &orders, const Table &lineitem);

ResultTable SolutionForProblem4(const Table &nation, const Table &supplier);

ResultTable SolutionForProblem5(const Table &lineitem);

#endif /* EXECUTOR_TRAINER_SOLUTIONS_H_ */