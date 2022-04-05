#include "disjoint_set_union.hpp"

bool DisjointSetUnion::Reserve(const size_t new_cap) {
  try {
    parents_.reserve(new_cap);
    subtree_sizes_.reserve(new_cap);
  } catch (std::bad_alloc&) {
    return false;
  }

  return true;
}

size_t DisjointSetUnion::SetsCnt() const {
  return parents_.size();
}

size_t DisjointSetUnion::AddSet() {
  size_t new_elem_tag = SetsCnt();

  try {
    parents_.push_back(new_elem_tag);
    subtree_sizes_.push_back(1);
  } catch (std::bad_alloc&) {
    parents_.pop_back();
    subtree_sizes_.pop_back();

    return INVALID_ELEM_TAG;
  }

  return new_elem_tag;
}

size_t DisjointSetUnion::Merge(size_t elem1_tag, size_t elem2_tag) {
  if (!IsTagValid(elem1_tag) || !IsTagValid(elem2_tag)) {
    return INVALID_ELEM_TAG;
  }

  size_t delegate1 = FindDelegate(elem1_tag);
  size_t delegate2 = FindDelegate(elem2_tag);

  if (delegate1 == delegate2) {
    return delegate1;
  }

  if (subtree_sizes_[elem1_tag] < subtree_sizes_[elem2_tag]) {
    std::swap(elem1_tag, elem2_tag);
  }
  parents_[elem2_tag] = elem1_tag;
  subtree_sizes_[elem1_tag] += subtree_sizes_[elem2_tag];

  return elem1_tag;
}

size_t DisjointSetUnion::FindDelegate(size_t elem_tag) {
  if (!IsTagValid(elem_tag)) {
    return INVALID_ELEM_TAG;
  }

  size_t res_tag = elem_tag;
  while (parents_[res_tag] != res_tag) {
    res_tag = parents_[res_tag];
  }

  size_t old_parent = parents_[elem_tag];
  while (old_parent != elem_tag) {
    old_parent = parents_[elem_tag];
    parents_[elem_tag] = res_tag;
    elem_tag = old_parent;
  }

  return res_tag;
}

size_t DisjointSetUnion::GetSubtreeSize(const size_t elem_tag) {
  if (!IsTagValid(elem_tag)) {
    return INVALID_ELEM_TAG;
  }

  return subtree_sizes_[elem_tag];
}

bool DisjointSetUnion::IsTagValid(const size_t elem_tag) const {
  return elem_tag < SetsCnt();
}
