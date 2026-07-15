#ifndef ALG_REF_CH07_QUICKSORT_H_
#define ALG_REF_CH07_QUICKSORT_H_

// Chapter 7: Quicksort.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 7.
// The original programs sorted raw C arrays a[l..r] using a global exch/less;
// here every routine is templated on a RandomAccessIterator range [lo, hi)
// and uses std::swap plus operator<, so any comparable type works.
//
// Variants provided:
//   Quicksort           basic recursive Lomuto/Hoare-style partition sort
//   HybridQuicksort     median-of-three pivot + insertion sort for small runs
//   ThreeWayQuicksort   Dijkstra 3-way partition, fast with many duplicates
//   QuickSelect         k-th smallest element in expected linear time
//
// Complexity (N elements):
//   Quicksort           avg O(N log N), worst O(N^2), in-place
//   HybridQuicksort     avg O(N log N), fewer swaps/compares in practice
//   ThreeWayQuicksort   O(N log N), O(N) when keys take few distinct values
//   QuickSelect         expected O(N), worst O(N^2)

#include <algorithm>
#include <iterator>

namespace ch07 {

// --- basic recursive quicksort -------------------------------------------

// Hoare-style partition of [lo, hi): pivot is the last element. Returns an
// iterator to the pivot's final resting position; all elements before it are
// <= pivot, all after are >= pivot.
template <class RandomIt>
RandomIt Partition(RandomIt lo, RandomIt hi) {
  RandomIt last = hi - 1;
  auto pivot = *last;
  RandomIt i = lo;
  for (RandomIt j = lo; j != last; ++j) {
    if (*j < pivot) {
      std::swap(*i, *j);
      ++i;
    }
  }
  std::swap(*i, *last);
  return i;
}

template <class RandomIt>
void Quicksort(RandomIt lo, RandomIt hi) {
  if (hi - lo <= 1) return;
  RandomIt p = Partition(lo, hi);
  Quicksort(lo, p);
  Quicksort(p + 1, hi);
}

// --- hybrid: median-of-three + insertion sort for small subfiles ----------

namespace detail {

// Straight insertion sort over [lo, hi); used to finish small subarrays.
template <class RandomIt>
void InsertionSort(RandomIt lo, RandomIt hi) {
  for (RandomIt i = lo + (lo != hi ? 1 : 0); i < hi; ++i) {
    auto v = *i;
    RandomIt j = i;
    while (j > lo && v < *(j - 1)) {
      *j = *(j - 1);
      --j;
    }
    *j = v;
  }
}

// Order lo, mid, last and place the median just before the last element so it
// can serve as the pivot; this guards against the worst case on sorted input.
template <class RandomIt>
void MedianOfThree(RandomIt lo, RandomIt hi) {
  RandomIt last = hi - 1;
  RandomIt mid = lo + (hi - lo) / 2;
  if (*mid < *lo) std::swap(*mid, *lo);
  if (*last < *lo) std::swap(*last, *lo);
  if (*last < *mid) std::swap(*last, *mid);
  // median is now at mid; stash it next to the pivot slot.
  std::swap(*mid, *(last - 1));
}

constexpr int kInsertionCutoff = 10;

template <class RandomIt>
void HybridSort(RandomIt lo, RandomIt hi) {
  if (hi - lo <= kInsertionCutoff) {
    InsertionSort(lo, hi);
    return;
  }
  MedianOfThree(lo, hi);
  RandomIt p = Partition(lo, hi);
  HybridSort(lo, p);
  HybridSort(p + 1, hi);
}

}  // namespace detail

template <class RandomIt>
void HybridQuicksort(RandomIt lo, RandomIt hi) {
  detail::HybridSort(lo, hi);
}

// --- three-way partitioning (Dijkstra "Dutch national flag") --------------

// Partitions [lo, hi) into < pivot, == pivot, > pivot; excellent when the
// input contains many equal keys.
template <class RandomIt>
void ThreeWayQuicksort(RandomIt lo, RandomIt hi) {
  if (hi - lo <= 1) return;
  auto pivot = *lo;
  RandomIt lt = lo;        // [lo, lt)  < pivot
  RandomIt gt = hi;        // [gt, hi)  > pivot
  RandomIt i = lo + 1;     // [lt, i)  == pivot, [i, gt) unseen
  while (i < gt) {
    if (*i < pivot) {
      std::swap(*lt, *i);
      ++lt;
      ++i;
    } else if (pivot < *i) {
      --gt;
      std::swap(*i, *gt);
    } else {
      ++i;
    }
  }
  ThreeWayQuicksort(lo, lt);
  ThreeWayQuicksort(gt, hi);
}

// --- quickselect: k-th smallest (0-based) ---------------------------------

// Rearranges [lo, hi) so that the element at lo + k is the one that would sit
// there in fully sorted order, and returns an iterator to it.
template <class RandomIt>
RandomIt QuickSelect(RandomIt lo, RandomIt hi, std::size_t k) {
  RandomIt target = lo + k;
  while (hi - lo > 1) {
    RandomIt p = Partition(lo, hi);
    if (target < p) {
      hi = p;
    } else if (target > p) {
      lo = p + 1;
    } else {
      return p;
    }
  }
  return lo;
}

}  // namespace ch07

#endif  // ALG_REF_CH07_QUICKSORT_H_
