// Chapter 2 driver: contrast sequential and binary search on a sorted vector.
//
// The demo builds a sorted vector of integers, searches for keys that are
// present and absent with both algorithms, and reports how many key
// comparisons each one used.  The comparison counts illustrate the theme of
// the chapter: sequential search does work proportional to N, while binary
// search does work proportional to log N.
//
//   ./ch02_analysis_main        # run the built-in demo (no arguments needed)

#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

#include "search.h"

using ch02::BinarySearch;
using ch02::SequentialSearch;

namespace {

// Report one search with both algorithms on the sorted vector `a`.
void Report(const std::vector<int>& a, int key) {
  std::size_t seq_cmps = 0, bin_cmps = 0;
  auto seq = SequentialSearch(a.begin(), a.end(), key, &seq_cmps);
  auto bin = BinarySearch(a.begin(), a.end(), key, &bin_cmps);

  const bool found = (seq != a.end());
  std::cout << "  key " << key << ": "
            << (found ? "found" : "absent")
            << "  |  sequential " << seq_cmps << " cmps"
            << ", binary " << bin_cmps << " cmps";
  if (found) {
    std::cout << "  (index " << std::distance(a.begin(), bin) << ")";
  }
  std::cout << '\n';
}

}  // namespace

int main() {
  // A sorted vector of the first N odd numbers: 1, 3, 5, ...
  const int kN = 64;
  std::vector<int> a;
  a.reserve(kN);
  for (int i = 0; i < kN; ++i) a.push_back(2 * i + 1);

  std::cout << "Sorted vector of " << kN << " odd numbers (1 .. "
            << a.back() << ").\n\n";

  std::cout << "Present keys:\n";
  Report(a, a.front());   // best case for sequential (first element)
  Report(a, a[kN / 2]);   // middle element
  Report(a, a.back());    // worst case for sequential (last element)

  std::cout << "\nAbsent keys:\n";
  Report(a, 0);           // below the range
  Report(a, 100);         // even number, inside the range but not present
  Report(a, 1000);        // above the range

  std::cout << "\nWith N = " << kN
            << ", worst-case sequential search approaches N comparisons "
            << "while binary search stays near log2(N) ~ 6.\n";
  return 0;
}
