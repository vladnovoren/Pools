#ifndef DISJOINT_SET_UNION_HPP
#define DISJOINT_SET_UNION_HPP

#include <vector>
#include <limits>

class DisjointSetUnion {
 public:
  bool Reserve(const size_t new_cap);

  size_t SetsCnt() const;

  size_t AddSet();

  size_t Merge(size_t elem1_tag, size_t elem2_tag);

  size_t FindDelegate(const size_t tag);

  size_t GetSubtreeSize(const size_t tag);

 public:
  static const size_t INVALID_ELEM_TAG = std::numeric_limits<size_t>::max();

 private:
  size_t FindDelegateRecImpl(const size_t elem_tag);

  bool IsTagValid(const size_t tag) const;

 private:
  std::vector<size_t> parents_;
  std::vector<size_t> subtree_sizes_;

};

#endif /* dsu.hpp */
