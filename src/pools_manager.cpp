#include "pools_manager.hpp"
#include "pool.hpp"

PoolsManager::PoolsManager() {
}

PoolsManager& PoolsManager::GetInstance() {
  static PoolsManager instance;
  return instance;
}

bool PoolsManager::Reserve(const size_t new_cap) {
  try {
    volumes_.reserve(new_cap);
  } catch (std::bad_alloc&) {
    return false;
  }
  
  return pools_set_.Reserve(new_cap);
}

size_t PoolsManager::AddPool(long water) {
  try {
    volumes_.push_back(water);
  } catch (std::bad_alloc& e) {
    return Pool::INVALID_POOL_TAG;
  }

  return pools_set_.AddSet();
}