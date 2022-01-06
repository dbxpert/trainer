#include <climits>
#include <vector>
#include <stdexcept>
#include "test_result.h"
#include "test.h"
#include "run_test.h"

static constexpr char ERROR_MESSAGE_HEADER = '0';
static constexpr char TEST_RESULT_MESSAGGE_HEADER = '1';

static inline std::string SerializeErrorMessage(std::string error) {
  std::vector<unsigned char> byte_array{ERROR_MESSAGE_HEADER};
  
  for (auto c : error) {
    byte_array.push_back(c); 
  }
  
  return std::string(byte_array.begin(), byte_array.end());
}

static inline void SerializeElapseTime(std::vector<unsigned char> &byte_array, long elapse_time) {
  for (std::size_t i = 0; i < sizeof(decltype(elapse_time)); ++i) {
    byte_array.push_back(elapse_time & 0xFF);
    elapse_time >>= CHAR_BIT;
  }
}

static inline std::string SerializeTestResult(TestResult result) {
  std::vector<unsigned char> byte_array{TEST_RESULT_MESSAGGE_HEADER};

  SerializeElapseTime(byte_array, result.user_elapse_time);
  SerializeElapseTime(byte_array, result.pace_maker_elapse_time);
  byte_array.push_back(static_cast<unsigned char>(result.success));

  return std::string(byte_array.begin(), byte_array.end());
}

std::string RunTest(const SQLHDBC connection, unsigned int problem_number) {
  Test test;
  std::string result;

  try {
    auto test_result = test.Run(connection, problem_number);
    result = SerializeTestResult(test_result);
  } catch (const std::runtime_error &e) {
    result = SerializeErrorMessage(std::string(e.what()));
  } 

  return result;
}
