#include "common.h"

static constexpr std::size_t CUSTOMER_TABLE_COL_CNT = 3;
static constexpr std::size_t LINEITEM_TABLE_COL_CNT = 8;
static constexpr std::size_t NATION_TABLE_COL_CNT = 2;
static constexpr std::size_t ORDERS_TABLE_COL_CNT = 4;
static constexpr std::size_t PART_TABLE_COL_CNT = 3;
static constexpr std::size_t PARTSUPP_TABLE_COL_CNT = 4;
static constexpr std::size_t REGION_TABLE_COL_CNT = 1;
static constexpr std::size_t SUPPLIER_TABLE_COL_CNT = 3;

std::array<std::size_t, TPCH_TABLE_COUNT> TPCH_TABLE_COLUMN_COUNT = {
  CUSTOMER_TABLE_COL_CNT,
  LINEITEM_TABLE_COL_CNT,
  NATION_TABLE_COL_CNT,
  ORDERS_TABLE_COL_CNT,
  PART_TABLE_COL_CNT,
  PARTSUPP_TABLE_COL_CNT,
  REGION_TABLE_COL_CNT,
  SUPPLIER_TABLE_COL_CNT
};

std::array<std::string, TPCH_TABLE_COUNT> TPCH_TABLE_NAMES = {
  "CUSTOMER",
  "LINEITEM",
  "NATION",
  "ORDERS",
  "PART",
  "PARTSUPP",
  "REGION",
  "SUPPLIER"
};

std::map<std::string, std::size_t> TPCH_TABLE_NAME_TO_INDEX = {
  {"CUSTOMER", 0},
  {"LINEITEM", 1},
  {"NATION", 2},
  {"ORDERS", 3},
  {"PART", 4},
  {"PARTSUPP", 5},
  {"REGION", 6},
  {"SUPPLIER", 7}
};