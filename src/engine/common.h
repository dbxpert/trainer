#ifndef EXECUTOR_TRAINER_ENGINE_COMMON_H_
#define EXECUTOR_TRAINER_ENGINE_COMMON_H_

#include <array>
#include <map>
#include <string>
#include <vector>

/* columnar table
 * Table
 * [[column 1], [column 2], [column 3], ...]
 */ 
using Table = std::vector<std::vector<float>>;
static constexpr std::size_t TPCH_TABLE_COUNT = 8;
static constexpr std::size_t PROBLEM_COUNT = 5;
extern std::array<std::string, TPCH_TABLE_COUNT> TPCH_TABLE_NAMES;
extern std::array<std::size_t, TPCH_TABLE_COUNT> TPCH_TABLE_COLUMN_COUNT;
extern std::map<std::string, std::size_t> TPCH_TABLE_NAME_TO_INDEX;
#endif /* EXECUTOR_TRAINER_ENGINE_COMMON_H_ */