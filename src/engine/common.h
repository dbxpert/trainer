#ifndef EXECUTOR_TRAINER_ENGINE_COMMON_H_
#define EXECUTOR_TRAINER_ENGINE_COMMON_H_

#include <array>
#include <map>
#include <string>
#include <vector>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

using shared_memory = boost::interprocess::managed_shared_memory;
using column_allocator = boost::interprocess::allocator<float, shared_memory::segment_manager>; 
using column_vector = boost::interprocess::vector<float, column_allocator>;
using table_allocator = boost::interprocess::allocator<column_vector, shared_memory::segment_manager>;
using table_vector = boost::interprocess::vector<column_vector, table_allocator>; 

/* columnar table
 * Table
 * [[column 1], [column 2], [column 3], ...]
 */ 
using SharedTable = table_vector;
using LocalTable = std::vector<std::vector<float>>;

static constexpr std::size_t TPCH_TABLE_COUNT = 8;
static constexpr std::size_t PROBLEM_COUNT = 5;
extern std::array<std::string, TPCH_TABLE_COUNT> TPCH_TABLE_NAMES;
extern std::array<std::size_t, TPCH_TABLE_COUNT> TPCH_TABLE_COLUMN_COUNT;
extern std::map<std::string, std::size_t> TPCH_TABLE_NAME_TO_INDEX;
extern std::array<std::size_t, PROBLEM_COUNT> COLUMN_COUNT_FOR_ANSWERS; 

#endif /* EXECUTOR_TRAINER_ENGINE_COMMON_H_ */