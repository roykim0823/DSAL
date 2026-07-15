// Chapter 10 driver: sort a sample vector of 32-bit unsigned integers with the
// three radix methods and confirm each result is sorted.
//
//   ./ch10_radix_sorting_main   # runs the built-in demo, no arguments needed

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

#include "radix_sort.h"

using ch10::Key;

namespace {

// A mix of small, large, and boundary keys to exercise every byte-digit.
const std::vector<Key> kSample = {
    170u,        45u,         75u,         90u,        802u,
    24u,         2u,          66u,         0u,         4294967295u,
    2147483648u, 1u,          16909060u,   255u,       256u,
    65535u,      65536u,      1000000u,    999999u,    123456789u,
};

bool IsSorted(const std::vector<Key>& a) {
  return std::is_sorted(a.begin(), a.end());
}

void Print(const std::vector<Key>& a) {
  for (Key k : a) std::cout << ' ' << k;
  std::cout << '\n';
}

void RunCase(const char* name, const std::vector<Key>& original,
             void (*sorter)(std::vector<Key>&)) {
  std::vector<Key> a = original;
  sorter(a);
  std::cout << std::left << std::setw(18) << name
            << (IsSorted(a) ? "sorted OK   " : "NOT SORTED  ");
  Print(a);
}

}  // namespace

int main() {
  std::cout << "Input (" << kSample.size() << " unsigned keys):\n ";
  Print(kSample);
  std::cout << '\n';

  RunCase("LSD radix", kSample, ch10::RadixLsd);
  RunCase("MSD radix", kSample, ch10::RadixMsd);
  RunCase("Binary quicksort", kSample, ch10::BinaryQuicksort);

  return 0;
}
