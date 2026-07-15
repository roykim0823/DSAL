#ifndef ALG_REF_CH12_ORDERED_ARRAY_ST_H_
#define ALG_REF_CH12_ORDERED_ARRAY_ST_H_

// Chapter 12: Symbol Tables and BSTs -- ordered-array symbol table.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 12.
// Keys are kept sorted in a std::vector so search is a binary search and
// select(k) is a direct index.  Insertion shifts elements, so it is the
// price paid for constant-time selection and logarithmic search.
//
// Complexity (N keys):
//   search / rank : O(log N)  (binary search)
//   select        : O(1)
//   insert        : O(N)      (shift to keep the array sorted)

#include <ostream>
#include <utility>
#include <vector>

namespace ch12 {

template <class Key, class Item>
class OrderedArrayST {
 public:
  int size() const { return static_cast<int>(entries_.size()); }

  // Insert or overwrite; keeps entries sorted by key. O(N).
  void insert(const Key& key, const Item& item) {
    int r = rank(key);
    if (r < size() && !(key < entries_[r].first) &&
        !(entries_[r].first < key)) {
      entries_[r].second = item;  // key present: overwrite
      return;
    }
    entries_.insert(entries_.begin() + r, {key, item});
  }

  // Pointer to the item stored under key, or nullptr. O(log N).
  const Item* search(const Key& key) const {
    int r = rank(key);
    if (r < size() && !(key < entries_[r].first) && !(entries_[r].first < key))
      return &entries_[r].second;
    return nullptr;
  }

  bool contains(const Key& key) const { return search(key) != nullptr; }

  // k-th smallest item (0-based); nullptr if out of range. O(1).
  const Item* select(int k) const {
    if (k < 0 || k >= size()) return nullptr;
    return &entries_[k].second;
  }

  // Number of keys strictly less than key, via binary search. O(log N).
  int rank(const Key& key) const {
    int lo = 0, hi = size();
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (entries_[mid].first < key)
        lo = mid + 1;
      else
        hi = mid;
    }
    return lo;
  }

  void show(std::ostream& os) const {
    for (const auto& e : entries_)
      os << e.first << " " << e.second << "\n";
  }

 private:
  std::vector<std::pair<Key, Item>> entries_;
};

}  // namespace ch12

#endif  // ALG_REF_CH12_ORDERED_ARRAY_ST_H_
