#ifndef EXECUTOR_TRAINER_SOLUTIONS_H_
#define EXECUTOR_TRAINER_SOLUTIONS_H_

#include <vector>

using Table = std::vector<std::vector<float>>;

Table SolutionForProblem1(const Table &lineitem);

Table SolutionForProblem2(const Table &part, const Table &partsupp);

Table SolutionForProblem3(const Table &customer, const Table &orders, const Table &lineitem);

Table SolutionForProblem4(const Table &nation, const Table &supplier);

Table SolutionForProblem5(const Table &lineitem);

#endif /* EXECUTOR_TRAINER_SOLUTIONS_H_ */