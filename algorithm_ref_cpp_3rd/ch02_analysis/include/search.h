#ifndef ALG_REF_CH02_SEARCH_H_
#define ALG_REF_CH02_SEARCH_H_

// Chapter 2: Principles of Algorithm Analysis -- sequential and binary search.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 2.
// The original programs took a raw C array plus explicit (l, r) bounds and
// returned an int index or -1.  Here the searches are function templates that
// take any random-access range [first, last) and return an iterator (or `last`
// when the key is absent), matching the conventions of <algorithm>.  Each
// variant can also report the number of key comparisons it performed, which is
// the whole point of the chapter: contrasting O(N) work against O(log N) work.
//
// Complexity (N = number of elements):
//   SequentialSearch   O(N)      comparisons -- works on any range
//   BinarySearch       O(log N)  comparisons -- requires a sorted range

#include <cstddef>
#include <iterator>

namespace ch02 {

// Linear scan: examine elements left to right until a match is found.
// Returns an iterator to the first element equal to `key`, or `last`.
// If `comparisons` is non-null, it receives the number of key comparisons.
template <typename It, typename T>
It SequentialSearch(It first, It last, const T& key,
                    std::size_t* comparisons = nullptr) {
  std::size_t count = 0;
  for (It it = first; it != last; ++it) {
    ++count;
    if (*it == key) {
      if (comparisons) *comparisons = count;
      return it;
    }
  }
  if (comparisons) *comparisons = count;
  return last;
}

// Binary search: repeatedly halve a *sorted* range around the midpoint.
// Returns an iterator to an element equal to `key`, or `last` if absent.
// If `comparisons` is non-null, it receives the number of key comparisons.
//
// Note: unlike the 1999 original, indices are replaced by iterators and the
// midpoint is computed as first + (len / 2) to avoid overflow on large ranges.
template <typename It, typename T>
It BinarySearch(It first, It last, const T& key,
                std::size_t* comparisons = nullptr) {
  std::size_t count = 0;
  It lo = first, hi = last;
  while (lo != hi) {
    It mid = lo;
    std::advance(mid, std::distance(lo, hi) / 2);
    ++count;
    if (*mid == key) {
      if (comparisons) *comparisons = count;
      return mid;
    }
    ++count;
    if (key < *mid) {
      hi = mid;         // search the left half [lo, mid)
    } else {
      lo = mid;
      ++lo;             // search the right half [mid+1, hi)
    }
  }
  if (comparisons) *comparisons = count;
  return last;
}

}  // namespace ch02

#endif  // ALG_REF_CH02_SEARCH_H_
