// Chapter 15 driver: demonstrate the two priority radix-search structures.
//
//   ./ch15_radix_search_main   # runs the built-in demo, no arguments needed
//
// It builds a Digital Search Tree over sample integer keys and a Ternary
// Search Trie over sample words, then searches for keys/words that are present
// and absent to show hits and misses.

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "digital_search_tree.h"
#include "ternary_search_trie.h"

using ch15::DigitalSearchTree;
using ch15::TernarySearchTrie;

namespace {

void DemoDigitalSearchTree() {
  std::cout << "== Digital Search Tree (integer keys) ==\n";
  DigitalSearchTree<std::string> dst;

  // key -> label (value); labels are just illustrative payloads.
  const std::vector<std::pair<std::uint32_t, std::string>> items = {
      {15, "fifteen"}, {6, "six"},  {12, "twelve"}, {3, "three"},
      {9, "nine"},     {1, "one"},  {8, "eight"},   {4, "four"},
      {11, "eleven"},  {13, "thirteen"}};
  for (const auto& kv : items) dst.insert(kv.first, kv.second);
  std::cout << "  inserted " << items.size() << " keys\n";

  const std::vector<std::uint32_t> queries = {9, 12, 1, 7, 20};
  for (std::uint32_t q : queries) {
    std::string val;
    if (dst.search(q, val))
      std::cout << "  search " << q << " -> found (" << val << ")\n";
    else
      std::cout << "  search " << q << " -> not found\n";
  }
}

void DemoTernarySearchTrie() {
  std::cout << "\n== Ternary Search Trie (string keys) ==\n";
  TernarySearchTrie<int> tst;

  // word -> its 1-based insertion order (value).
  const std::vector<std::string> words = {"now",  "is",   "the",  "time",
                                          "for",  "all",  "good", "people",
                                          "sea",  "shells"};
  int order = 1;
  for (const std::string& w : words) tst.insert(w, order++);
  std::cout << "  inserted " << words.size() << " words\n";

  const std::vector<std::string> queries = {"time", "sea",  "shells",
                                            "she",  "good", "bad"};
  for (const std::string& q : queries) {
    int val;
    if (tst.search(q, val))
      std::cout << "  search \"" << q << "\" -> found (insert #" << val
                << ")\n";
    else
      std::cout << "  search \"" << q << "\" -> not found\n";
  }
}

}  // namespace

int main() {
  DemoDigitalSearchTree();
  DemoTernarySearchTrie();
  return 0;
}
