#include <climits>
#include <vector>
#include <stdexcept>
#include "test_result.h"
#include "test.h"
#include "run_test.h"

static inline std::string SerializeErrorMessage(std::string error) {
  std::vector<unsigned char> byte_array;

  // flag for success
  byte_array.push_back('0');
  for (auto c : error) {
    byte_array.push_back(c); 
  }
  
  return std::string(byte_array.begin(), byte_array.end());
}

static inline std::string SerializeTestResult(TestResult result) {
  std::vector<unsigned char> byte_array;

  // flag for success
  byte_array.push_back('1');

  auto user_time = result.user_elapse_time;
  for (int i = 0; i < sizeof(decltype(user_time)); ++i) {
    byte_array.push_back(user_time & 0xFF);
    user_time >>= CHAR_BIT;
  }

  auto pm_time = result.pace_maker_elapse_time;
  for (int i = 0; i < sizeof(decltype(pm_time)); ++i) {
    byte_array.push_back(pm_time & 0xFF);
    pm_time >>= CHAR_BIT;
  }

  byte_array.push_back(static_cast<unsigned char>(result.success));

  return std::string(byte_array.begin(), byte_array.end());
}

std::string RunTest(unsigned int problem_number) {
  Test test;
  std::string result;

  try {
    auto test_result = test.Run(problem_number);
    result = SerializeTestResult(test_result);
  } catch (const std::runtime_error &e) {
    result = SerializeErrorMessage(std::string(e.what()));
  } 

  return result;
}
