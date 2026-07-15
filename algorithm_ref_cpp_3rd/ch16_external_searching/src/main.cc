// Chapter 16 driver: build a B-tree symbol table, insert sample keys (with a
// small branching factor so pages split and the tree grows), then search for
// keys that are present and absent.
//
//   ./ch16_external_searching_main   # runs the built-in demo, no args needed

#include <iostream>
#include <string>
#include <vector>

#include "btree_st.h"

using ch16::BTreeST;

int main() {
  // M = 4 -> each page holds at most 3 entries, forcing several splits.
  BTreeST<std::string, int, 4> st;

  // 15 sample keys (the classic S E A R C H I N G E X A M P L E letters,
  // de-duplicated) mapped to an insertion counter.
  const std::vector<std::string> keys = {
      "S", "E", "A", "R", "C", "H", "I", "N",
      "G", "X", "M", "P", "L", "B", "T"};

  std::cout << "Inserting " << keys.size() << " keys into a B-tree (M=4):\n ";
  for (size_t i = 0; i < keys.size(); ++i) {
    st.insert(keys[i], static_cast<int>(i));
    std::cout << ' ' << keys[i];
  }
  std::cout << "\n\n";

  std::cout << "Tree: size=" << st.size() << " height=" << st.height()
            << " (levels above the leaves)\n";
  std::cout << st.LevelDump() << "\n";

  const std::vector<std::string> probes = {"A", "R", "X", "T", "Z", "Q", "E"};
  std::cout << "Searches:\n";
  int found = 0;
  for (const std::string& k : probes) {
    int value;
    if (st.search(k, value)) {
      std::cout << "  " << k << " -> found (value " << value << ")\n";
      ++found;
    } else {
      std::cout << "  " << k << " -> not found\n";
    }
  }

  std::cout << "\n" << found << " of " << probes.size()
            << " probe keys were present.\n";
  return 0;
}
