#ifndef DISJOINT_SET_UNION_HPP
#define DISJOINT_SET_UNION_HPP

#include <vector>

class DisjointSetUnion {
 public:
  void AddSet(const size_t tag);
  void MergeSets(const size_t tag1, const size_t tag2);

  size_t FindParent(const size_t tag);

 private:
  static const size_t CAPACITY = 12000000;

  std::vector<size_t> parents_{CAPACITY};
  std::vector<size_t> ranks_{CAPACITY};

};

#endif /* dsu.hpp */
