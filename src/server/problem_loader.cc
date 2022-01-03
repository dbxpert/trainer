#include <string>
#include "problem_loader.h"
#include "database_loader.h"

void ProblemLoader::Load(unsigned int problem_number) {
  Connect();
  LoadInputTables(SearchProblemTable(problem_number));
}

void ProblemLoader::Connect() {
  if (!connector_.Connect()) {
    throw std::runtime_error("Database Connection failed");
  }
}

static inline std::vector<bool> GenerateFetchInfo(std::vector<int> fetch_result) {
  std::vector<bool> fetch_info(fetch_result.size() - 1);
  for (int i = 1; i < fetch_result.size(); ++i) {
    if (fetch_result[i] == 1)
      fetch_info[i] = true;
    else
      fetch_info[i] = false;
  } 

  return fetch_info;
}

std::vector<bool> ProblemLoader::SearchProblemTable(unsigned int problem_number) {
  DatabaseLoader loader(connector_);
  std::string query("select * from problem_table where problem_number = ");
  loader.SetSql(query + std::to_string(problem_number) + ";");

  auto problem_info = loader.Load();

  if (problem_info.empty()) {
    throw std::runtime_error("No such problem");
  }

  return GenerateFetchInfo(problem_info[0]);
}

static inline std::string GenerateFetchQuery(int table_idx) { 
  std::vector<std::string> table_names = {};
  std::string query("select * from ");
  return query + table_names[table_idx] + ";";
}

void ProblemLoader::LoadInputTables(std::vector<bool> fetch_info) {
  DatabaseLoader loader(connector_);

  for (int i = 0; i < fetch_info.size(); ++i) {
    if (!fetch_info[i])
      continue;

    auto query = GenerateFetchQuery(i);
    loader.SetSql(query);
    input_tables_.push_back(loader.Load());
  }
}
