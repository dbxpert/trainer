#ifndef EXECUTOR_TRAINER_SOLUTIONS_H_
#define EXECUTOR_TRAINER_SOLUTIONS_H_

#include <vector>

using Table = std::vector<std::vector<float>>;

/* TPC-H Q1 */
Table SolutionForProblem1(const Table &lineitem);

/* TPC-H Q4 */
Table SolutionForProblem2(const Table &orders, const Table &lineitem);

/* TPC-H Q5 */
Table SolutionForProblem3(const Table &customer, const Table &orders, const Table &lineitem,
                          const Table &supplier, const Table &nation, const Table &region);

/* TPC-H Q10 */
Table SolutionForProblem4(const Table &customer, const Table &orders, const Table &lineitem);

/* TPC-H Q18 */
Table SolutionForProblem5(const Table &orders, const Table &lineitem);

#endif /* EXECUTOR_TRAINER_SOLUTIONS_H_ */