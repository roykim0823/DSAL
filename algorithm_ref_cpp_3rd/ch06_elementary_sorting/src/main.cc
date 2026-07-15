// Chapter 6 driver: run each elementary sorting method on a built-in sample
// and confirm the result is ordered.  No arguments required.
//
//   ./ch06_elementary_sorting_main

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "sorts.h"

namespace {

template <class Item>
void Print(const std::vector<Item>& a) {
  for (const Item& x : a) std::cout << x << ' ';
}

template <class Item>
bool IsSorted(const std::vector<Item>& a) {
  return std::is_sorted(a.begin(), a.end());
}

template <class Item, class Sort>
void Run(const std::string& name, std::vector<Item> a, Sort sort) {
  sort(a);
  std::cout << name << ":\n  ";
  Print(a);
  std::cout << "\n  sorted: " << (IsSorted(a) ? "yes" : "no") << "\n\n";
}

}  // namespace

int main() {
  const std::vector<int> sample = {5, 3, 8, 1, 9, 2, 7, 0, 6, 4, 3, 8, 1};

  std::cout << "Input: ";
  Print(sample);
  std::cout << "\n\n";

  Run<int>("selection sort", sample, [](std::vector<int>& v) { ch06::selection(v); });
  Run<int>("insertion sort", sample, [](std::vector<int>& v) { ch06::insertion(v); });
  Run<int>("bubble sort", sample, [](std::vector<int>& v) { ch06::bubble(v); });
  Run<int>("shellsort", sample, [](std::vector<int>& v) { ch06::shellsort(v); });

  // Distribution counting needs to know the key upper bound M (keys in [0, M)).
  Run<int>("distribution counting", sample,
           [](std::vector<int>& v) { ch06::distcount(v, 10); });

  return 0;
}
