#ifndef EXECUTOR_TRAINER_TABLE_H_
#define EXECUTOR_TRAINER_TABLE_H_

#include <vector>
#include <array>

/* columnar table
 * Table
 * [[column 1], [column 2], [column 3], ...]
 */ 
using Table = std::vector<std::vector<float>>;
static constexpr std::size_t TPCH_TABLE_COUNT = 8;
static constexpr std::size_t CUSTOMER_TABLE_COL_CNT = 3;
static constexpr std::size_t LINEITEM_TABLE_COL_CNT = 8;
static constexpr std::size_t NATION_TABLE_COL_CNT = 2;
static constexpr std::size_t ORDERS_TABLE_COL_CNT = 4;
static constexpr std::size_t PART_TABLE_COL_CNT = 3;
static constexpr std::size_t PARTSUPP_TABLE_COL_CNT = 4;
static constexpr std::size_t REGION_TABLE_COL_CNT = 1;
static constexpr std::size_t SUPPLIER_TABLE_COL_CNT = 3;
extern std::array<std::size_t, TPCH_TABLE_COUNT> TPCH_TABLE_COLUMN_COUNT;
#endif /* EXECUTOR_TRAINER_TABLE_H_ */
