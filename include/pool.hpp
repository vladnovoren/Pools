#ifndef POOL_HPP
#define POOL_HPP

#include <cassert>
#include <cstddef>
#include "disjoint_set_union.hpp"

class Pool {
 public:
  Pool(const double water = 0);

  double Measure();

  void Connect(Pool& other);

  void AddWater(const double water);

  static bool Reserve(const size_t new_cap);

  size_t GetTag() const;

  bool IsValid() const;

 public:
  static const size_t INVALID_POOL_TAG = std::numeric_limits<size_t>::max();

 private:
  bool is_valid_ = true;

  size_t tag_ = DisjointSetUnion::INVALID_ELEM_TAG;

  static DisjointSetUnion pools_set_;
  static std::vector<double> volumes_;

};

#endif /* pool.hpp */
