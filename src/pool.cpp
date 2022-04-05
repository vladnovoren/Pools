#include "pool.hpp"

DisjointSetUnion Pool::pools_set_;
std::vector<double> Pool::volumes_;

Pool::Pool(const double water) {
  try {
    volumes_.push_back(water);
  } catch (std::bad_alloc&) {
    is_valid_ = false;
  }

  if ((tag_ = pools_set_.AddSet()) == DisjointSetUnion::INVALID_ELEM_TAG) {
    is_valid_ = false;
    volumes_.pop_back();
  }
}

double Pool::Measure() {
  size_t delegate_tag = pools_set_.FindDelegate(tag_);
  size_t this_group_size = pools_set_.GetSubtreeSize(delegate_tag);

  assert(this_group_size);

  return volumes_[delegate_tag] / this_group_size;
}

void Pool::Connect(Pool& other) {
  if (this == &other) {
    return;
  }

  size_t this_delegate_tag = pools_set_.FindDelegate(tag_);
  size_t other_delegate_tag = pools_set_.FindDelegate(other.GetTag());

  if (this_delegate_tag == other_delegate_tag) {
    return;
  }

  size_t this_group_size = pools_set_.GetSubtreeSize(this_delegate_tag);
  size_t other_group_size = pools_set_.GetSubtreeSize(other_delegate_tag);

  double this_group_volume = volumes_[this_delegate_tag];
  double other_group_volume = volumes_[other_delegate_tag];

  size_t result_tag = pools_set_.Merge(this_delegate_tag, other_delegate_tag);
  volumes_[result_tag] = this_group_volume + other_group_volume;
}

void Pool::AddWater(const double water) {
  size_t delegate_tag = pools_set_.FindDelegate(tag_);
  volumes_[delegate_tag] += water;
}

bool Pool::Reserve(const size_t new_cap) {
  try {
    volumes_.reserve(new_cap);
  } catch (std::bad_alloc&) {
    false;
  }

  return pools_set_.Reserve(new_cap);
}

size_t Pool::GetTag() const {
  return tag_;
}

bool Pool::IsValid() const {
  return is_valid_;
}

size_t Pool::GetSize() const {
  return pools_set_.GetSubtreeSize(pools_set_.FindDelegate(tag_));
}