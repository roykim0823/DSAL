// Chapter 11 driver: sort a sample vector with Batcher's odd-even merge sort
// (a sorting network) and verify the result is ordered.  No arguments needed.
//
//   ./ch11_special_purpose_sorts_main
//
// The input length must be a power of two; here N = 16.

#include <algorithm>
#include <iostream>
#include <vector>

#include "batcher_sort.h"

namespace {

void Print(const char* label, const std::vector<int>& v) {
  std::cout << label;
  for (int x : v) std::cout << ' ' << x;
  std::cout << '\n';
}

}  // namespace

int main() {
  // A scrambled power-of-two length sample (N = 16).
  std::vector<int> v = {15, 3, 9, 1, 12, 7, 0, 14,
                        6, 11, 2, 13, 8, 4, 10, 5};

  Print("before:", v);
  ch11::batchersort(v.begin(), v.end());
  Print("after :", v);

  bool ok = std::is_sorted(v.begin(), v.end());
  std::cout << "sorted: " << (ok ? "yes" : "no") << '\n';

  // Also demonstrate the perfect-shuffle helpers on the sorted array.
  std::vector<int> s = v;
  ch11::shuffle(s.begin(), 0, static_cast<int>(s.size()) - 1);
  Print("shuffle:", s);
  ch11::unshuffle(s.begin(), 0, static_cast<int>(s.size()) - 1);
  Print("unshuf :", s);
  std::cout << "shuffle round-trip: " << (s == v ? "ok" : "FAILED") << '\n';

  return ok ? 0 : 1;
}
