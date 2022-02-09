#include "sharer.h"
#include "table.h"
#include <stdexcept>

using LocalTable = std::vector<std::vector<float>>;

void Sharer::ShareResultTable(const LocalTable &table) {
  shared_memory shm_segment(boost::interprocess::open_only, "TRAINER_SHM_KEY");
  auto result_table = GetObjectFromSharedMemory<Table>(shm_segment, "RESULT_TABLE");

  if (table.size() != result_table->size())
    return;

  for (std::size_t i = 0; i < table.size(); ++i) {
    auto &src_col = table[i];
    auto &target_col = result_table->at(i);
  
    target_col.insert(target_col.begin(), src_col.begin(), src_col.end());
  } 
}

void Sharer::ShareElapsedTime(const long elapsed_time) {
  shared_memory shm_segment(boost::interprocess::open_only, "TRAINER_SHM_KEY");
  auto dest = GetObjectFromSharedMemory<long>(shm_segment, "ELAPSED_TIME");
  
  *dest = elapsed_time; 
}