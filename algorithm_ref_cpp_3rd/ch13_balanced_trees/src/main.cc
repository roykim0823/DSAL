// Chapter 13 driver: build a red-black BST and a skip list from the same set
// of sample keys, run present/absent searches against both, and print each
// structure's in-order traversal (which must come out sorted).
//
//   ./ch13_balanced_trees_main   # no arguments; runs the built-in demo
//
// The skip list seeds its level-choosing RNG with a fixed value, so the run
// is fully deterministic.

#include <iostream>
#include <vector>

#include "red_black_bst.h"
#include "skip_list.h"

using ch13::RedBlackBST;
using ch13::SkipList;

namespace {

// Sample keys (unsorted, no duplicates) inserted into both structures.
const std::vector<int> kSample = {50, 30, 70, 20, 40, 60, 80,
                                  10, 25, 35, 45, 55, 65, 75, 85};

// Keys probed by search: some present, some absent.
const std::vector<int> kProbes = {40, 85, 10, 99, 55, 42, 5};

void PrintKeys(const std::vector<int>& keys) {
  for (size_t i = 0; i < keys.size(); ++i) {
    if (i) std::cout << ' ';
    std::cout << keys[i];
  }
  std::cout << '\n';
}

bool IsSorted(const std::vector<int>& keys) {
  for (size_t i = 1; i < keys.size(); ++i)
    if (keys[i - 1] > keys[i]) return false;
  return true;
}

template <typename ST>
void RunSearches(const ST& st) {
  for (int key : kProbes) {
    std::cout << "  search(" << key << ") -> "
              << (st.contains(key) ? "found" : "absent") << '\n';
  }
}

}  // namespace

int main() {
  std::cout << "Inserting " << kSample.size() << " keys:\n  ";
  PrintKeys(kSample);

  RedBlackBST rbt;
  SkipList skip(12345u);  // fixed seed -> deterministic levels
  for (int key : kSample) {
    rbt.insert(key);
    skip.insert(key);
  }

  std::cout << "\n== Red-black BST ==\n";
  RunSearches(rbt);
  std::vector<int> rb_order = rbt.inorder();
  std::cout << "  inorder: ";
  PrintKeys(rb_order);
  std::cout << "  sorted?  " << (IsSorted(rb_order) ? "yes" : "no") << '\n';

  std::cout << "\n== Skip list ==\n";
  RunSearches(skip);
  std::vector<int> skip_order = skip.inorder();
  std::cout << "  inorder: ";
  PrintKeys(skip_order);
  std::cout << "  sorted?  " << (IsSorted(skip_order) ? "yes" : "no") << '\n';

  bool ok = IsSorted(rb_order) && IsSorted(skip_order) &&
            rb_order.size() == kSample.size() &&
            skip_order.size() == kSample.size();
  std::cout << "\nSelf-check: " << (ok ? "PASS" : "FAIL") << '\n';
  return ok ? 0 : 1;
}
