#include "engine.h"
#include <stdexcept>
#include <climits>
#include <iostream>

void Engine::Prepare(const SQLHDBC connection) {
  std::cout << "Loading Tables From Trainer DB..." << std::endl;
  problem_loader_.Load(connection);
  std::cout << "Loading Answers From Trainer DB..." << std::endl;
  result_checker_.LoadAnswers(connection);
  std::cout << "Trainer server started up" << std::endl;
}

static inline const std::string SerializeResult(bool success, long elapsed) {
  std::vector<unsigned char> byte_array;

  for (std::size_t i = 0; i < sizeof(decltype(elapsed)); ++i) {
    byte_array.push_back(elapsed & 0xFF);
    elapsed >>= CHAR_BIT;
  }
  byte_array.push_back(static_cast<unsigned char>(success));

  return std::string(byte_array.begin(), byte_array.end());
}

const std::string Engine::Run(unsigned int problem_number) {
  auto &input_tables = problem_loader_.GetInputTables();
  auto result = solution_runner_.Run(problem_number, input_tables);
  auto success = result_checker_.Check(problem_number, result);
  return SerializeResult(success, solution_runner_.GetElapsedTime());
}