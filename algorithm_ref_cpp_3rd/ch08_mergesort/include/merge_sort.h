#ifndef ALG_REF_CH08_MERGE_SORT_H_
#define ALG_REF_CH08_MERGE_SORT_H_

// Chapter 8: Mergesort -- array-based variants.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 8.
// The original programs merged through a fixed-size static `aux[maxN]`; here
// the auxiliary storage is a std::vector sized to the input, and every routine
// is templated on a random-access container of comparable Items.
//
// Routines:
//   MergeAB        -- merge two sorted ranges [a..) and [b..) into c.
//   TopDownSort    -- recursive divide-and-conquer mergesort.
//   BottomUpSort   -- non-recursive, doubling merge passes.
//
// Complexity (N items):
//   comparisons/moves    O(N log N)   -- guaranteed, worst == average
//   extra space          O(N)         -- auxiliary buffer
//   stability            stable

#include <cstddef>
#include <vector>

namespace ch08 {

// Two-way merge of sorted a[0..n) and b[0..m) into c[0..n+m).
// This is the abstract building block from which the array sorts are built.
template <class Item>
void MergeAB(Item* c, const Item* a, std::size_t n, const Item* b,
             std::size_t m) {
  std::size_t i = 0, j = 0;
  for (std::size_t k = 0; k < n + m; ++k) {
    if (i == n) {
      c[k] = b[j++];
    } else if (j == m) {
      c[k] = a[i++];
    } else {
      c[k] = (a[i] < b[j]) ? a[i++] : b[j++];
    }
  }
}

namespace detail {

// Abstract in-place merge of a[lo..mid] and a[mid+1..hi], both sorted, using
// aux as scratch.  Elements are copied into aux, then merged back into a.
template <class Item>
void Merge(std::vector<Item>& a, std::vector<Item>& aux, std::size_t lo,
           std::size_t mid, std::size_t hi) {
  for (std::size_t k = lo; k <= hi; ++k) aux[k] = a[k];

  std::size_t i = lo, j = mid + 1;
  for (std::size_t k = lo; k <= hi; ++k) {
    if (i > mid) {
      a[k] = aux[j++];
    } else if (j > hi) {
      a[k] = aux[i++];
    } else if (aux[j] < aux[i]) {
      a[k] = aux[j++];
    } else {
      a[k] = aux[i++];
    }
  }
}

template <class Item>
void SortRange(std::vector<Item>& a, std::vector<Item>& aux, std::size_t lo,
               std::size_t hi) {
  if (hi <= lo) return;
  std::size_t mid = lo + (hi - lo) / 2;
  SortRange(a, aux, lo, mid);
  SortRange(a, aux, mid + 1, hi);
  Merge(a, aux, lo, mid, hi);
}

}  // namespace detail

// Top-down recursive mergesort: split in half, sort each half, merge.
template <class Item>
void TopDownSort(std::vector<Item>& a) {
  if (a.size() < 2) return;
  std::vector<Item> aux(a.size());
  detail::SortRange(a, aux, 0, a.size() - 1);
}

// Bottom-up mergesort: merge runs of length 1, 2, 4, ... in successive passes.
template <class Item>
void BottomUpSort(std::vector<Item>& a) {
  std::size_t n = a.size();
  if (n < 2) return;
  std::vector<Item> aux(n);
  for (std::size_t width = 1; width < n; width += width) {
    for (std::size_t lo = 0; lo + width < n; lo += width + width) {
      std::size_t mid = lo + width - 1;
      std::size_t hi = lo + width + width - 1;
      if (hi >= n) hi = n - 1;
      detail::Merge(a, aux, lo, mid, hi);
    }
  }
}

}  // namespace ch08

#endif  // ALG_REF_CH08_MERGE_SORT_H_
