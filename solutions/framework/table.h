#ifndef EXECUTOR_TRAINER_SOLUTIONS_TABLE_H_
#define EXECUTOR_TRAINER_SOLUTIONS_TABLE_H_

#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

using shared_memory = boost::interprocess::managed_shared_memory;
using column_allocator = boost::interprocess::allocator<float, shared_memory::segment_manager>;
using column_vector = boost::interprocess::vector<float, column_allocator>;
using table_allocator = boost::interprocess::allocator<column_vector, shared_memory::segment_manager>;
using table_vector = boost::interprocess::vector<column_vector, table_allocator>;

using Table = table_vector;

template <typename T>
static inline T *GetObjectFromSharedMemory(shared_memory &shm_segment, const char *name) {
  return shm_segment.find<T>(name).first;
}

#endif /* EXECUTOR_TRAINER_SOLUTIONS_TABLE_H_ */