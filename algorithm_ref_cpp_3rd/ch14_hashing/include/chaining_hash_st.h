#ifndef ALG_REF_CH14_CHAINING_HASH_ST_H_
#define ALG_REF_CH14_CHAINING_HASH_ST_H_

// Chapter 14: Hashing -- separate-chaining symbol table.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 14.
// The book stored a raw array of linked-list heads; here each bucket is a
// std::vector of (key, value) pairs.  Collisions are resolved by chaining:
// keys that hash to the same bucket share one list.
//
// Complexity (N keys, M buckets, load factor alpha = N/M):
//   search / insert / remove : O(1 + alpha) expected
//
// Keys are std::string, values are Value (template parameter, int in demo).

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "hash_functions.h"

namespace ch14 {

template <typename Value>
class ChainingHashST {
 public:
  explicit ChainingHashST(std::size_t buckets = 97)
      : buckets_(buckets == 0 ? 1 : buckets), n_(0) {}

  std::size_t size() const { return n_; }
  bool empty() const { return n_ == 0; }

  // Insert or overwrite the value associated with key.
  void insert(const std::string& key, const Value& value) {
    auto& chain = buckets_[HashString(key, buckets_.size())];
    for (auto& entry : chain) {
      if (entry.first == key) {
        entry.second = value;
        return;
      }
    }
    chain.emplace_back(key, value);
    ++n_;
  }

  // Return a pointer to the value for key, or nullptr if absent.
  const Value* search(const std::string& key) const {
    const auto& chain = buckets_[HashString(key, buckets_.size())];
    for (const auto& entry : chain)
      if (entry.first == key) return &entry.second;
    return nullptr;
  }

  bool contains(const std::string& key) const { return search(key) != nullptr; }

  // Remove key if present; return true if something was removed.
  bool remove(const std::string& key) {
    auto& chain = buckets_[HashString(key, buckets_.size())];
    for (std::size_t i = 0; i < chain.size(); ++i) {
      if (chain[i].first == key) {
        chain[i] = chain.back();
        chain.pop_back();
        --n_;
        return true;
      }
    }
    return false;
  }

 private:
  std::vector<std::vector<std::pair<std::string, Value>>> buckets_;
  std::size_t n_;
};

}  // namespace ch14

#endif  // ALG_REF_CH14_CHAINING_HASH_ST_H_
