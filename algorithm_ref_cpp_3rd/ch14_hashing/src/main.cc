// Chapter 14 driver: build symbol tables with two collision strategies and
// exercise insert / search / remove.  No arguments required.
//
//   ./ch14_hashing_main            # run the built-in demo

#include <iostream>
#include <string>
#include <vector>

#include "chaining_hash_st.h"
#include "hash_functions.h"
#include "linear_probing_hash_st.h"

using ch14::ChainingHashST;
using ch14::HashString;
using ch14::LinearProbingHashST;

namespace {

struct Entry {
  std::string key;
  int value;
};

// Sample key/value pairs: word -> arbitrary payload.
const std::vector<Entry> kSample = {
    {"apple", 1},  {"banana", 2}, {"cherry", 3},     {"date", 4},
    {"elder", 5},  {"fig", 6},    {"grape", 7},      {"honeydew", 8},
    {"kiwi", 9},   {"lemon", 10}, {"mango", 11},     {"nectarine", 12}};

template <typename Table>
void ReportSearch(const Table& t, const std::string& key) {
  const int* v = t.search(key);
  std::cout << "  search(\"" << key << "\") -> ";
  if (v)
    std::cout << *v << '\n';
  else
    std::cout << "(absent)\n";
}

}  // namespace

int main() {
  std::cout << "Hash of sample keys (M = 97):\n";
  for (const Entry& e : kSample)
    std::cout << "  " << HashString(e.key, 97) << "  " << e.key << '\n';

  // --- Separate chaining ---------------------------------------------------
  std::cout << "\n[Separate chaining]\n";
  ChainingHashST<int> chain;
  for (const Entry& e : kSample) chain.insert(e.key, e.value);
  std::cout << "  inserted " << chain.size() << " keys\n";
  ReportSearch(chain, "cherry");
  ReportSearch(chain, "durian");  // absent
  chain.insert("cherry", 42);     // overwrite
  ReportSearch(chain, "cherry");
  chain.remove("cherry");
  std::cout << "  removed \"cherry\"; size now " << chain.size() << '\n';
  ReportSearch(chain, "cherry");  // absent now

  // --- Linear probing ------------------------------------------------------
  std::cout << "\n[Linear probing]\n";
  LinearProbingHashST<int> probe(8);  // small start forces a resize
  for (const Entry& e : kSample) probe.insert(e.key, e.value);
  std::cout << "  inserted " << probe.size() << " keys, capacity "
            << probe.capacity() << '\n';
  ReportSearch(probe, "grape");
  ReportSearch(probe, "papaya");  // absent

  // Remove a key and confirm the rest of the cluster is still reachable.
  probe.remove("grape");
  std::cout << "  removed \"grape\"; size now " << probe.size() << '\n';
  ReportSearch(probe, "grape");  // absent now
  std::cout << "  cluster integrity after remove:\n";
  for (const Entry& e : kSample) {
    if (e.key == "grape") continue;
    if (!probe.contains(e.key)) {
      std::cout << "    MISSING: " << e.key << '\n';
    }
  }
  std::cout << "  all remaining keys still found.\n";

  return 0;
}
