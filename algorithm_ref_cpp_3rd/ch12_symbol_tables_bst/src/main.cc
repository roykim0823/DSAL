// Chapter 12 driver: exercise the binary search tree symbol table (and, for
// contrast, the ordered-array table).  No arguments required -- it inserts a
// fixed sample of integer keys and demonstrates each operation.
//
//   ./ch12_symbol_tables_bst_main
//
// The Item here is just a payload string; keys are ints.

#include <iostream>
#include <string>
#include <vector>

#include "bst.h"
#include "ordered_array_st.h"

using ch12::BST;
using ch12::OrderedArrayST;

namespace {

struct Sample {
  int key;
  const char* value;
};

// A scramble of distinct integer keys (with one duplicate to show overwrite).
const std::vector<Sample> kSample = {
    {50, "fifty"},  {30, "thirty"}, {70, "seventy"}, {20, "twenty"},
    {40, "forty"},  {60, "sixty"},  {80, "eighty"},  {10, "ten"},
    {25, "twenty-five"}, {30, "THIRTY(updated)"}};

}  // namespace

int main() {
  BST<int, std::string> st;

  std::cout << "Inserting " << kSample.size() << " (key,value) pairs...\n";
  for (const Sample& s : kSample) st.insert(s.key, std::string(s.value));

  std::cout << "\nDistinct keys in table: " << st.size() << "\n";

  std::cout << "\nInorder (sorted) contents:\n";
  st.show(std::cout);

  std::cout << "\nSearches:\n";
  for (int q : {40, 30, 99}) {
    const std::string* v = st.search(q);
    std::cout << "  search(" << q << ") -> "
              << (v ? *v : std::string("not found")) << "\n";
  }

  std::cout << "\nOrder statistics:\n";
  for (int k : {0, 3, st.size() - 1}) {
    const std::string* v = st.select(k);
    std::cout << "  select(" << k << ") -> " << (v ? *v : std::string("(none)"))
              << "\n";
  }
  for (int key : {10, 45, 80}) {
    std::cout << "  rank(" << key << ") = " << st.rank(key) << "\n";
  }

  const int kRemove = 30;
  std::cout << "\nRemoving key " << kRemove << " (an internal, two-child node)"
            << "...\n";
  st.remove(kRemove);
  std::cout << "Distinct keys now: " << st.size() << "\n";
  std::cout << "Inorder contents after removal:\n";
  st.show(std::cout);

  // Ordered-array table: same data, binary-search based.
  std::cout << "\n--- Ordered-array symbol table (binary search) ---\n";
  OrderedArrayST<int, std::string> arr;
  for (const Sample& s : kSample) arr.insert(s.key, std::string(s.value));
  std::cout << "select(2) -> " << *arr.select(2) << "\n";
  std::cout << "rank(60)  = " << arr.rank(60) << "\n";
  const std::string* av = arr.search(99);
  std::cout << "search(99) -> " << (av ? *av : std::string("not found"))
            << "\n";

  return 0;
}
