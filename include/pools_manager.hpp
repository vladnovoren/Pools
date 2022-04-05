#ifndef POOLS_MANAGER_HPP
#define POOLS_MANAGER_HPP

#include "disjoint_set_union.hpp"

class Pool;

class PoolsManager {
 public:
  static PoolsManager& GetInstance();

  bool Reserve(const size_t new_cap);

  size_t AddPool(long water = 0);

  long GetRawPoolWater(const size_t pool_id);

 private:
  PoolsManager();

  std::vector<long> volumes_;
  DisjointSetUnion pools_set_;

};

#endif /* pools_manager.hpp */
