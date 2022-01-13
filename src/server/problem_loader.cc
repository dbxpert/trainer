#include <string>
#include <stdexcept>
#include <cassert>
#include "problem_loader.h"
#include "database_adapter.h"

ProblemLoader::ProblemLoader() : input_tables_(TPCH_TABLE_COUNT) {}

void ProblemLoader::Load(const SQLHDBC connection, unsigned int problem_number) {
  std::vector<bool> fetch_info;
  try {
    fetch_info = SearchProblemTable(connection, problem_number);
  } catch (const std::runtime_error &e) {
    std::string what(e.what());
    if (what.compare("No such problem") == 0)
      assert(false && "No such problem");
  }
  LoadInputTables(connection, fetch_info);
}

static inline std::vector<bool> GenerateFetchInfo(std::vector<float> fetch_result) {
  std::vector<bool> fetch_info(fetch_result.size() - 1);
  for (std::size_t i = 1; i < fetch_result.size(); ++i) {
    if (fetch_result[i] == 1)
      fetch_info[i - 1] = true;
    else
      fetch_info[i - 1] = false;
  } 

  return fetch_info;
}

std::vector<bool> ProblemLoader::SearchProblemTable(const SQLHDBC connection, unsigned int problem_number) {
  DatabaseAdapter db_adapter;
  std::string query("select * from problem_table where problem_number = ");
  db_adapter.SetSQL(query + std::to_string(problem_number) + ";");

  auto problem_info = db_adapter.Load(connection);

  if (problem_info.empty()) {
    throw std::runtime_error("No such problem");
  }

  return GenerateFetchInfo(problem_info[0]);
}

static inline std::string GenerateFetchQuery(int table_idx) {
  std::vector<std::string> table_names = {"CUSTOMER", "LINEITEM", "NATION", "ORDERS",
                                          "PART",     "PARTSUPP", "REGION", "SUPPLIER"};
  std::string query("select * from ");
  return query + table_names[table_idx] + ";";
}

void ProblemLoader::LoadInputTables(const SQLHDBC connection, std::vector<bool> fetch_info) {
  DatabaseAdapter db_adapter;

  for (std::size_t i = 0; i < fetch_info.size(); ++i) {
    if (!fetch_info[i])
      continue;

    db_adapter.SetSQL(GenerateFetchQuery(i));
    
    auto &dest = input_tables_[i];
    while (!db_adapter.FetchFinished()) {
      auto result = db_adapter.Load(connection);
      dest.insert(dest.begin(), result.begin(), result.end());
    } 
  }
}
