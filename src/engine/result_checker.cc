#include "result_checker.h"
#include "database_adapter.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>

static const std::string ANSWER_FOR_PROBLEM_1 = "select sum(l_quantity) as sum_qty, "
                                                "sum(l_extendedprice) as sum_base_price, "
                                                "sum(l_extendedprice*(1-l_discount)) as sum_disc_price, "
                                                "sum(l_extendedprice*(1-l_discount)*(1+l_tax)) as sum_charge, "
                                                "avg(l_quantity) as avg_qty, "
                                                "avg(l_extendedprice) as avg_price, "
                                                "avg(l_discount) as avg_disc, "
                                                "count(*) as count_order "
                                                "from lineitem "
                                                "group by l_linenumber;";

static const std::string ANSWER_FOR_PROBLEM_2 = "select p_partkey, max_margin from ("
                                                "select p_partkey, max(margin) max_margin from ("
                                                "select p_partkey, (p_retailprice - ps_supplycost) margin "
                                                "from part, partsupp "
                                                "where 1=1 "
                                                "and ps_partkey = p_partkey "
                                                "and p_size = 50 "
                                                "and p_retailprice >= ps_supplycost) "
                                                "group by p_partkey "
                                                "order by max_margin desc) "
                                                "where rownum <= 1;";

static const std::string ANSWER_FOR_PROBLEM_3 = "select c_nationkey, revenue from "
                                                "(select c_nationkey, sum(l_extendedprice * (1 - l_discount)) as revenue "
                                                "from customer, orders, lineitem "
                                                "where c_custkey = o_custkey "
                                                "and l_orderkey = o_orderkey "
                                                "group by c_nationkey "
                                                "order by revenue desc) "
                                                "where rownum <= 10;";

static const std::string ANSWER_FOR_PROBLEM_4 = "select n_regionkey, "
                                                "3 * (avg(s_acctbal) - median(s_acctbal)) / stddev(s_acctbal) skewness "
                                                "from nation, supplier "
                                                "where 1=1 "
                                                "and s_nationkey = n_nationkey "
                                                "group by n_regionkey "
                                                "order by n_regionkey;";

static const std::string ANSWER_FOR_PROBLEM_5 = "select l_linenumber, count(l_linenumber) count from "
                                                "(select l_linenumber, "
                                                "rank() over (partition by l_orderkey order by l_quantity desc) rank "
                                                "from lineitem) "
                                                "where rank = 1 "
                                                "group by l_linenumber;";

static const std::array<std::string, PROBLEM_COUNT> ANSWER_FOR_PROBLEMS = {
  ANSWER_FOR_PROBLEM_1,
  ANSWER_FOR_PROBLEM_2,
  ANSWER_FOR_PROBLEM_3,
  ANSWER_FOR_PROBLEM_4,
  ANSWER_FOR_PROBLEM_5
};

template <typename T>
static inline std::vector<unsigned int> GetSortedRowNumber(const T &target);
static inline bool CheckRowByRow(const SharedTable &result, const LocalTable &answer);
static inline bool CheckRowCount(const SharedTable &result, std::size_t answer_row_cnt);
static inline bool CheckColumnCount(std::size_t result_col_cnt, std::size_t answer_col_cnt);
static inline bool CheckSize(const SharedTable &result, const LocalTable &answer);

ResultChecker::ResultChecker() : answers_(PROBLEM_COUNT) {
  for (std::size_t i = 0; i < PROBLEM_COUNT; ++i) {
    auto &answer = answers_[i];
    answer.reserve(COLUMN_COUNT_FOR_ANSWERS[i]);
    
    for (std::size_t i = 0; i < answer.capacity(); ++i)
      answer[i].clear();
  }
}

void ResultChecker::LoadAnswers(const SQLHDBC connection) {
  DatabaseAdapter adapter;  
  for (unsigned int i = 0; i < PROBLEM_COUNT; ++i) {
    adapter.SetSQL(ANSWER_FOR_PROBLEMS[i]);
    auto &dest = answers_[i];
    while (!adapter.FetchFinished()) {
      auto result = adapter.Load(connection);
      dest.insert(dest.begin(), result.begin(), result.end());
    }
  }
}

bool ResultChecker::Check(const SharedTable &result, unsigned int problem_number) {
  assert(problem_number <= PROBLEM_COUNT && "Wrong problem number");
  auto &answer = answers_[problem_number - 1];
  if (!CheckSize(result, answer))
    return false;

  return CheckRowByRow(result, answer);
}

static inline bool CheckSize(const SharedTable &result, const LocalTable &answer) {
  if (!CheckColumnCount(result.size(), answer.size()))
    return false;

  if (!CheckRowCount(result, answer[0].size()))
    return false;

  return true;
}

static inline bool CheckColumnCount(std::size_t result_col_cnt, std::size_t answer_col_cnt) {
  return result_col_cnt == answer_col_cnt;
}

static inline bool CheckRowCount(const SharedTable &result, std::size_t answer_row_cnt) {
  auto row_cnt = result[0].size();
  if (row_cnt != answer_row_cnt)
    return false;

  for (auto col_iter : result) {
    if (col_iter.size() != row_cnt)
      return false;
  }

  return true;
}

static inline bool CheckRowByRow(const SharedTable &result, const LocalTable &answer) {
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

template <typename T>
static inline std::vector<unsigned int> GetSortedRowNumber(const T &target) {
  std::vector<unsigned int> row_number;
  for (std::size_t i = 0; i < target[0].size(); ++i)
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