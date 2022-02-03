#ifndef EXECUTOR_TRAINER_ENGINE_TABLE_MANAGER_H_
#define EXECUTOR_TRAINER_ENGINE_TABLE_MANAGER_H_

#include "common.h"
#include <array>

class TableManager {
 public:
  TableManager();
  ~TableManager();

  SharedTable &GetTableReference(const std::size_t table_idx) const;
  SharedTable &GetTableReference(const std::string &table_name) const;

  /* Default shared memory size is 2G */ 
  static constexpr std::size_t DFLT_SHM_SIZE = 2147483648UL;
 
 private:
  void AllocateTableInSharedMemory(const std::size_t table_idx);

  shared_memory shm_segment_; 
  std::array<SharedTable *, TPCH_TABLE_COUNT> tables_;
};

#endif /* EXECUTOR_TRAINER_ENGINE_TABLE_MANAGER_H_ */