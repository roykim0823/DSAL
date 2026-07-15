#ifndef ALG_REF_CH14_LINEAR_PROBING_HASH_ST_H_
#define ALG_REF_CH14_LINEAR_PROBING_HASH_ST_H_

// Chapter 14: Hashing -- open-addressing symbol table (linear probing).
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 14.
// Keys live directly in one array; on a collision we scan forward
// ((i+1) % M) until an empty slot or a matching key is found.  The table
// keeps the load factor below 1/2 by doubling its capacity, mirroring the
// book's expand() routine.  Deletion re-inserts the rest of the cluster so
// no reachable key is stranded behind an empty slot.
//
// Complexity (load factor alpha < 1):
//   search / insert / remove : O(1) expected (amortized for insert w/ resize)

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "hash_functions.h"

namespace ch14 {

template <typename Value>
class LinearProbingHashST {
 public:
  explicit LinearProbingHashST(std::size_t capacity = 16)
      : keys_(capacity < 4 ? 4 : capacity),
        vals_(capacity < 4 ? 4 : capacity),
        used_(capacity < 4 ? 4 : capacity, false),
        n_(0) {}

  std::size_t size() const { return n_; }
  bool empty() const { return n_ == 0; }
  std::size_t capacity() const { return keys_.size(); }

  // Insert or overwrite the value associated with key.
  void insert(const std::string& key, const Value& value) {
    if (2 * n_ >= keys_.size()) resize(2 * keys_.size());
    std::size_t m = keys_.size();
    std::size_t i = HashString(key, m);
    while (used_[i]) {
      if (keys_[i] == key) {
        vals_[i] = value;
        return;
      }
      i = (i + 1) % m;
    }
    keys_[i] = key;
    vals_[i] = value;
    used_[i] = true;
    ++n_;
  }

  // Return a pointer to the value for key, or nullptr if absent.
  const Value* search(const std::string& key) const {
    std::size_t m = keys_.size();
    for (std::size_t i = HashString(key, m); used_[i]; i = (i + 1) % m)
      if (keys_[i] == key) return &vals_[i];
    return nullptr;
  }

  bool contains(const std::string& key) const { return search(key) != nullptr; }

  // Remove key if present; return true if something was removed.  Every key in
  // the rest of the cluster is deleted and re-inserted to close the gap.
  bool remove(const std::string& key) {
    std::size_t m = keys_.size();
    std::size_t i = HashString(key, m);
    while (used_[i] && keys_[i] != key) i = (i + 1) % m;
    if (!used_[i]) return false;

    used_[i] = false;
    --n_;

    i = (i + 1) % m;
    while (used_[i]) {
      std::string rehash_key = keys_[i];
      Value rehash_val = vals_[i];
      used_[i] = false;
      --n_;
      insert(rehash_key, rehash_val);
      i = (i + 1) % m;
    }

    if (n_ > 0 && 8 * n_ <= keys_.size()) resize(keys_.size() / 2);
    return true;
  }

 private:
  void resize(std::size_t new_capacity) {
    if (new_capacity < 4) new_capacity = 4;
    LinearProbingHashST<Value> temp(new_capacity);
    for (std::size_t i = 0; i < keys_.size(); ++i)
      if (used_[i]) temp.insert(keys_[i], vals_[i]);
    keys_ = std::move(temp.keys_);
    vals_ = std::move(temp.vals_);
    used_ = std::move(temp.used_);
    n_ = temp.n_;
  }

  std::vector<std::string> keys_;
  std::vector<Value> vals_;
  std::vector<bool> used_;
  std::size_t n_;
};

}  // namespace ch14

#endif  // ALG_REF_CH14_LINEAR_PROBING_HASH_ST_H_
