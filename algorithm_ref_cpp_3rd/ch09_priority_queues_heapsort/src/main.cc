// Chapter 9 driver: exercise the heap-based priority queue and heapsort.
//
//   ./ch09_priority_queues_heapsort_main   # runs the built-in demo
//
// No arguments required.  The demo inserts a handful of values into a max
// priority queue and pops them in descending order, then heapsorts a sample
// vector and confirms the result is sorted.

#include <algorithm>
#include <iostream>
#include <vector>

#include "priority_queue.h"

using ch09::heapsort;
using ch09::PQ;
using ch09::PQsort;

namespace {

template <class Item>
void PrintVec(const std::vector<Item>& v) {
  std::cout << "[";
  for (std::size_t i = 0; i < v.size(); ++i) {
    if (i) std::cout << ", ";
    std::cout << v[i];
  }
  std::cout << "]";
}

}  // namespace

int main() {
  // --- Priority queue: insert several, pop max repeatedly. ---
  const std::vector<int> input = {5, 3, 9, 1, 7, 8, 2, 6, 4, 0};
  std::cout << "Priority queue demo\n";
  std::cout << "  inserting: ";
  PrintVec(input);
  std::cout << "\n";

  PQ<int> pq(static_cast<int>(input.size()));
  for (int x : input) pq.insert(x);

  std::cout << "  popping max repeatedly: ";
  std::vector<int> popped;
  while (!pq.empty()) popped.push_back(pq.getmax());
  PrintVec(popped);
  std::cout << "\n";

  bool pq_ok = std::is_sorted(popped.rbegin(), popped.rend());
  std::cout << "  descending order? " << (pq_ok ? "yes" : "NO") << "\n\n";

  // --- Heapsort a sample vector + sorted check. ---
  std::vector<int> a = {42, 17, 99, 3, 58, 21, 76, 8, 64, 30, 11, 90};
  std::cout << "Heapsort demo\n";
  std::cout << "  before: ";
  PrintVec(a);
  std::cout << "\n";

  heapsort(a);

  std::cout << "  after:  ";
  PrintVec(a);
  std::cout << "\n";
  bool hs_ok = std::is_sorted(a.begin(), a.end());
  std::cout << "  sorted? " << (hs_ok ? "yes" : "NO") << "\n\n";

  // --- PQsort as an alternative sort driven by the PQ. ---
  std::vector<int> b = {12, 4, 7, 1, 9, 3, 15, 6};
  std::cout << "PQsort demo\n";
  std::cout << "  before: ";
  PrintVec(b);
  std::cout << "\n";

  PQsort(b, 0, static_cast<int>(b.size()) - 1);

  std::cout << "  after:  ";
  PrintVec(b);
  std::cout << "\n";
  bool pqs_ok = std::is_sorted(b.begin(), b.end());
  std::cout << "  sorted? " << (pqs_ok ? "yes" : "NO") << "\n";

  return (pq_ok && hs_ok && pqs_ok) ? 0 : 1;
}
