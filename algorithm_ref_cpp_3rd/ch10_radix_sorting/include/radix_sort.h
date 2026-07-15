#ifndef ALG_REF_CH10_RADIX_SORT_H_
#define ALG_REF_CH10_RADIX_SORT_H_

// Chapter 10: Radix Sorting.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 10.
// The original programs sorted raw C arrays of a generic Item using macro
// helpers (digit, bin, ch).  Here the keys are 32-bit unsigned integers held
// in std::vector<std::uint32_t> and every routine works over an inclusive
// index range [l, r].  Radix methods examine the key one "piece" at a time
// instead of comparing whole keys:
//
//   digit accessors  -- pull one bit or one byte out of a key, MSB first.
//   BinaryQuicksort  -- radix exchange sort; partitions on one bit per level.
//   RadixMsd         -- most-significant-digit (byte) distribution sort.
//   RadixLsd         -- least-significant-digit (byte) distribution sort.
//
// Constants (fixed for 32-bit unsigned keys):
//   R        = 256   radix: number of distinct values of one byte-digit.
//   kBitsWord = 32   number of bits in a key.
//   kBytesWord = 4   number of byte-digits in a key.
//
// Complexity (N keys, w = kBytesWord byte-digits, b = kBitsWord bit-digits):
//   BinaryQuicksort  O(b * N)   in place, examines up to b bits.
//   RadixMsd         O(w * N)   plus O(R) counters per recursive call.
//   RadixLsd         O(w * N)   stable, w counting passes over N keys.

#include <cstdint>
#include <vector>

namespace ch10 {

using Key = std::uint32_t;

// Radix and word geometry for 32-bit unsigned keys.
constexpr int kBitsWord = 32;               // bits per key
constexpr int kR = 256;                     // radix (one byte)
constexpr int kBitsPerDigit = 8;            // bits per byte-digit
constexpr int kBytesWord = kBitsWord / kBitsPerDigit;  // 4 byte-digits

// Cut over to insertion sort for small subfiles.
constexpr int kInsertionThreshold = 16;

// Bit-digit accessor: bit number d of key x, counting from the most
// significant bit (d == 0).  Returns 0 or 1.
inline int BitDigit(Key x, int d) {
  return static_cast<int>((x >> (kBitsWord - 1 - d)) & 1u);
}

// Byte-digit accessor: byte number d of key x, counting from the most
// significant byte (d == 0).  Returns a value in [0, kR).
inline int ByteDigit(Key x, int d) {
  return static_cast<int>((x >> (kBitsWord - (d + 1) * kBitsPerDigit)) &
                          (kR - 1));
}

// Plain insertion sort over [l, r]; used as the small-subfile base case.
inline void InsertionSort(std::vector<Key>& a, int l, int r) {
  for (int i = l + 1; i <= r; ++i) {
    Key v = a[i];
    int j = i;
    while (j > l && a[j - 1] > v) {
      a[j] = a[j - 1];
      --j;
    }
    a[j] = v;
  }
}

// ---- Binary quicksort (radix exchange sort) -------------------------------
//
// Partitions the subfile [l, r] on bit d (0 = most significant): keys with a
// 0 bit move left, keys with a 1 bit move right, then recurse on the next
// bit.  In place; O(kBitsWord * N).
inline void BinaryQuicksort(std::vector<Key>& a, int l, int r, int d) {
  if (r <= l || d >= kBitsWord) return;
  int i = l, j = r;
  while (i != j) {
    while (BitDigit(a[i], d) == 0 && i < j) ++i;
    while (BitDigit(a[j], d) == 1 && j > i) --j;
    std::swap(a[i], a[j]);
  }
  if (BitDigit(a[r], d) == 0) ++j;
  BinaryQuicksort(a, l, j - 1, d + 1);
  BinaryQuicksort(a, j, r, d + 1);
}

// Convenience entry point.
inline void BinaryQuicksort(std::vector<Key>& a) {
  if (!a.empty())
    BinaryQuicksort(a, 0, static_cast<int>(a.size()) - 1, 0);
}

// ---- MSD radix sort -------------------------------------------------------
//
// Distributes [l, r] into kR bins by byte-digit d (0 = most significant),
// then recurses on each bin using the next digit.  Stable within the counting
// pass; O(kBytesWord * N).  'aux' is a scratch buffer sized like 'a'.
inline void RadixMsd(std::vector<Key>& a, std::vector<Key>& aux, int l, int r,
                     int d) {
  if (d >= kBytesWord) return;
  if (r - l <= kInsertionThreshold) {
    InsertionSort(a, l, r);
    return;
  }
  int count[kR + 1] = {0};
  for (int i = l; i <= r; ++i) ++count[ByteDigit(a[i], d) + 1];
  for (int j = 1; j < kR + 1; ++j) count[j] += count[j - 1];
  for (int i = l; i <= r; ++i) aux[l + count[ByteDigit(a[i], d)]++] = a[i];
  for (int i = l; i <= r; ++i) a[i] = aux[i];
  // count[k] now marks the start (relative to l) of bin k+1; recurse per bin.
  RadixMsd(a, aux, l, l + count[0] - 1, d + 1);
  for (int j = 0; j < kR - 1; ++j)
    RadixMsd(a, aux, l + count[j], l + count[j + 1] - 1, d + 1);
}

// Convenience entry point.
inline void RadixMsd(std::vector<Key>& a) {
  if (a.empty()) return;
  std::vector<Key> aux(a.size());
  RadixMsd(a, aux, 0, static_cast<int>(a.size()) - 1, 0);
}

// ---- LSD radix sort -------------------------------------------------------
//
// Counting-sorts the whole file on each byte-digit from least significant
// (d = kBytesWord-1) up to most significant (d = 0).  Stable; O(kBytesWord*N).
inline void RadixLsd(std::vector<Key>& a, int l, int r) {
  std::vector<Key> aux(a.size());
  for (int d = kBytesWord - 1; d >= 0; --d) {
    int count[kR + 1] = {0};
    for (int i = l; i <= r; ++i) ++count[ByteDigit(a[i], d) + 1];
    for (int j = 1; j < kR + 1; ++j) count[j] += count[j - 1];
    for (int i = l; i <= r; ++i) aux[l + count[ByteDigit(a[i], d)]++] = a[i];
    for (int i = l; i <= r; ++i) a[i] = aux[i];
  }
}

// Convenience entry point.
inline void RadixLsd(std::vector<Key>& a) {
  if (!a.empty()) RadixLsd(a, 0, static_cast<int>(a.size()) - 1);
}

}  // namespace ch10

#endif  // ALG_REF_CH10_RADIX_SORT_H_
