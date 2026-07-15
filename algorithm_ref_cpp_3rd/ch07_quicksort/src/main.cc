// Chapter 7 driver: demonstrate the quicksort family on a sample vector.
//
//   ./ch07_quicksort_main   # runs the built-in demo, no arguments needed
//
// It sorts the same data with each variant, verifies the result is ordered,
// then uses quickselect to pull out order statistics without a full sort.

#include <iostream>
#include <string>
#include <vector>

#include "quicksort.h"

namespace {

const std::vector<int> kSample = {3, 7, 3, 1, 9, 3, 8, 2, 7,
                                  0, 5, 3, 6, 4, 1, 9, 2, 8};

void Print(const std::string& label, const std::vector<int>& v) {
  std::cout << label;
  for (int x : v) std::cout << ' ' << x;
  std::cout << '\n';
}

bool IsSorted(const std::vector<int>& v) {
  for (std::size_t i = 1; i < v.size(); ++i)
    if (v[i] < v[i - 1]) return false;
  return true;
}

// Run one sort variant on a fresh copy and report whether it produced order.
template <class SortFn>
void Demo(const std::string& name, SortFn sort) {
  std::vector<int> v = kSample;
  sort(v.begin(), v.end());
  Print(name + ":\n ", v);
  std::cout << "  sorted? " << (IsSorted(v) ? "yes" : "NO") << "\n\n";
}

}  // namespace

int main() {
  Print("input:\n ", kSample);
  std::cout << '\n';

  Demo("Quicksort (basic)",
       [](std::vector<int>::iterator b, std::vector<int>::iterator e) {
         ch07::Quicksort(b, e);
       });
  Demo("HybridQuicksort (median-of-3 + insertion)",
       [](std::vector<int>::iterator b, std::vector<int>::iterator e) {
         ch07::HybridQuicksort(b, e);
       });
  Demo("ThreeWayQuicksort (duplicate keys)",
       [](std::vector<int>::iterator b, std::vector<int>::iterator e) {
         ch07::ThreeWayQuicksort(b, e);
       });

  std::cout << "QuickSelect (k-th smallest, 0-based):\n";
  for (std::size_t k : {std::size_t{0}, kSample.size() / 2, kSample.size() - 1}) {
    std::vector<int> v = kSample;  // quickselect rearranges in place
    auto it = ch07::QuickSelect(v.begin(), v.end(), k);
    std::cout << "  k=" << k << " -> " << *it << '\n';
  }

  return 0;
}
