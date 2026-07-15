#ifndef ALG_REF_CH11_BATCHER_SORT_H_
#define ALG_REF_CH11_BATCHER_SORT_H_

// Chapter 11: Special-Purpose Sorts -- sorting networks.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 11.
// The original programs operated on raw C arrays with a global maxN buffer;
// here everything is templated on RandomAccessIterator / Item and the helpers
// use std::vector for scratch space.  The core building block is compexch, a
// compare-exchange comparator; a sorting network is just a fixed schedule of
// such comparators, independent of the data values.
//
//   compexch(a, b)               -- swap so that a <= b
//   shuffle / unshuffle          -- perfect shuffle permutations
//   batchersort(begin, end)      -- Batcher's odd-even merge sort
//
// Complexity (N a power of two):
//   batchersort   O(N (log N)^2) comparators, O((log N)^2) parallel depth.
//   shuffle/unshuffle            O(N) each.

#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

namespace ch11 {

// Compare-exchange: order the two items so that x <= y afterwards.
// This is the sole primitive from which every network below is built.
template <class Item>
void compexch(Item& x, Item& y) {
  using std::swap;
  if (y < x) swap(x, y);
}

// Perfect shuffle of a[l..r] (inclusive): interleaves the two halves so that
// the low half and high half alternate.  Inverse of unshuffle.
template <class Iter>
void shuffle(Iter a, int l, int r) {
  using Item = typename std::iterator_traits<Iter>::value_type;
  int m = (l + r) / 2;
  std::vector<Item> aux(r - l + 1);
  int i, j;
  for (i = l, j = 0; i <= r; i += 2, ++j) {
    aux[i - l] = a[l + j];
    aux[i - l + 1] = a[m + 1 + j];
  }
  for (i = l; i <= r; ++i) a[i] = aux[i - l];
}

// Inverse perfect shuffle of a[l..r] (inclusive): de-interleaves alternating
// elements back into a low half followed by a high half.
template <class Iter>
void unshuffle(Iter a, int l, int r) {
  using Item = typename std::iterator_traits<Iter>::value_type;
  int m = (l + r) / 2;
  std::vector<Item> aux(r - l + 1);
  int i, j;
  for (i = l, j = 0; i <= r; i += 2, ++j) {
    aux[l + j - l] = a[i];
    aux[m + 1 + j - l] = a[i + 1];
  }
  for (i = l; i <= r; ++i) a[i] = aux[i - l];
}

// Batcher's odd-even merge sort as a bottom-up sorting network over a[l..r].
// Requires N = r - l + 1 to be a power of two.  The comparator schedule is
// data-independent, which is exactly what makes it a "network" sort.
template <class Iter>
void batchersort(Iter a, int l, int r) {
  int N = r - l + 1;
  for (int p = 1; p < N; p += p)
    for (int k = p; k > 0; k /= 2)
      for (int j = k % p; j + k < N; j += (k + k))
        for (int i = 0; i < N - j - k; ++i)
          if ((j + i) / (p + p) == (j + i + k) / (p + p))
            compexch(a[l + j + i], a[l + j + i + k]);
}

// Convenience overload: sort an entire container/range in place.
// The length must be a power of two.
template <class Iter>
void batchersort(Iter begin, Iter end) {
  int n = static_cast<int>(std::distance(begin, end));
  if (n < 2) return;
  batchersort(begin, 0, n - 1);
}

}  // namespace ch11

#endif  // ALG_REF_CH11_BATCHER_SORT_H_
