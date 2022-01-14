#include "result_checker.h"
#include "database_adapter.h"
#include <string>
#include <array>
#include <algorithm>
#include <cassert>

static const std::string ANSWER_FOR_PROBLEM_1 = "select sum(l_quantity) as sum_qty, "
                                                "sum(l_extendedprice) as sum_base_price, "
                                                "sum(l_extendedprice*(1-l_discount)) as sum_disc_price, "
                                                "sum(l_extendedprice*(1-l_discount)*(1+l_tax)) as sum_charge, "
                                                "avg(l_quantity) as avg_qty, "
                                                "avg(l_extendedprice) as avg_price, "
                                                "avg(l_discount) as avg_disc, "
                                                "count(*) as count_order "
                                                "from lineitem;";

static const std::string ANSWER_FOR_PROBLEM_2 = "select max(p_retailprice) from part, partsupp "
                                                "where 1=1 "
                                                "and p_partkey = ps_partkey "
                                                "and p_size = 50 "
                                                "and ps_supplycost <= (select avg(ps_supplycost) from partsupp;";

static const std::string ANSWER_FOR_PROBLEM_3 = "select revenue from "
                                                "(select sum(l_extendedprice * (1 - l_discount)) as revenue "
                                                "from customer, orders, lineitem "
                                                "where c_custkey = o_custkey "
                                                "and l_orderkey = o_orderkey "
                                                "group by c_nationkey "
                                                "order by revenue desc) "
                                                "where rownum <= 10;";

static const std::string ANSWER_FOR_PROBLEM_4 = "select n_regionkey, n_nationkey, avg(s_acctbal) avg "
                                                "from nation, supplier "
                                                "where 1=1 "
                                                "and s_nationkey = n_nationkey "
                                                "group by rollup (n_regionkey, n_nationkey);";

static const std::string ANSWER_FOR_PROBLEM_5 = "select o_orderkey, o_totalprice from orders, lineitem "
                                                "where o_orderkey in (select l_orderkey from lineitem "
                                                "group by l_orderkey having sum(l_quantity) > 300) "
                                                "and o_orderkey = l_orderkey;";

static const std::array<std::string, PROBLEM_COUNT> ANSWER_SQL = {
  ANSWER_FOR_PROBLEM_1,
  ANSWER_FOR_PROBLEM_2,
  ANSWER_FOR_PROBLEM_3,
  ANSWER_FOR_PROBLEM_4,
  ANSWER_FOR_PROBLEM_5
};

void ResultChecker::LoadAnswers(const SQLHDBC connection) {
  DatabaseAdapter adapter;  
  for (unsigned int i = 0; i < PROBLEM_COUNT; ++i) {
    adapter.SetSQL(ANSWER_SQL[i]);
    answers_.emplace_back(adapter.Load(connection));
  }
}

static inline std::vector<unsigned int> GetSortedRowNumber(const Table &target) {
  std::vector<unsigned int> row_number;
  for (std::size_t i = 0; i < target.size(); ++i)
    row_number.emplace_back(i);

  std::sort(row_number.begin(), row_number.end(), 
            [&target](const unsigned int &i, const unsigned int &j) {
              for (auto iter : target) {
                if (iter[i] < iter[j])
                  return true;
                else if (iter[i] > iter[j])
                  return false;
              }
              return false;
            });
  return row_number;
}

static inline bool CheckRowByRow(const Table &result, const Table &answer) {
  auto sorted_rownum_for_result = GetSortedRowNumber(result);
  auto sorted_rownum_for_answer = GetSortedRowNumber(answer);

  bool ret = true;
  for (std::size_t i = 0; i < result[0].size(); ++i) {
    auto result_rownum = sorted_rownum_for_result[i];
    auto answer_rownum = sorted_rownum_for_answer[i];

    for (std::size_t j = 0; j < result.size(); ++j) {
      ret &= (result[j][result_rownum] == answer[j][answer_rownum]);
    }
  }
  return ret;
}

static inline bool CheckSize(const Table &result, std::size_t correct_col_cnt, std::size_t correct_row_cnt) {
  if (result.size() != correct_col_cnt)
    return false;

  auto row_cnt = result[0].size();
  if (row_cnt != correct_row_cnt)
    return false;

  for (auto col_iter : result) {
    if (col_iter.size() != row_cnt)
      return false; 
  }

  return true;
}

bool ResultChecker::Check(unsigned int problem_number, const Table &result) {
  assert(problem_number <= PROBLEM_COUNT && "Wrong problem number");

  auto &answer = answers_[problem_number - 1];
  if (!CheckSize(result, answer.size(), answer[0].size()))
    return false;

  return CheckRowByRow(result, answer);
}