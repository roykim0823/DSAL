// Chapter 1 driver: solve the connectivity problem with the four union-find
// strategies.  Reads whitespace-separated integer pairs "p q" and, for the
// weighted+path-compression solver, prints each pair that connects two
// previously separate components.
//
//   ./ch01_introduction            # run the built-in sample
//   ./ch01_introduction pairs.txt  # first token = N, then "p q" pairs
//
// A pairs file looks like:
//   10
//   4 3
//   3 8
//   ...

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "union_find.h"

using ch01::QuickFind;
using ch01::QuickUnion;
using ch01::WeightedQuickUnion;
using ch01::WeightedQuickUnionPC;

namespace {

struct Pair {
  int p, q;
};

// Sample from Sedgewick, Chapter 1 (N = 10).
const int kSampleN = 10;
const std::vector<Pair> kSample = {{4, 3}, {3, 8}, {6, 5}, {9, 4}, {2, 1},
                                   {8, 9}, {5, 0}, {7, 2}, {6, 1}, {1, 0},
                                   {6, 7}};

bool ReadFile(const char* path, int& n, std::vector<Pair>& pairs) {
  std::ifstream in(path);
  if (!in) {
    std::cerr << "Error: cannot open " << path << '\n';
    return false;
  }
  in >> n;
  Pair e;
  while (in >> e.p >> e.q) pairs.push_back(e);
  return true;
}

}  // namespace

int main(int argc, char* argv[]) {
  int n = kSampleN;
  std::vector<Pair> pairs = kSample;

  if (argc > 1 && !ReadFile(argv[1], n, pairs)) return 1;

  QuickFind qf(n);
  QuickUnion qu(n);
  WeightedQuickUnion wqu(n);
  WeightedQuickUnionPC wqupc(n);

  int connections = 0;
  std::cout << "New connections (weighted quick-union + path compression):\n";
  for (const Pair& e : pairs) {
    qf.unite(e.p, e.q);
    qu.unite(e.p, e.q);
    wqu.unite(e.p, e.q);
    if (!wqupc.connected(e.p, e.q)) {
      wqupc.unite(e.p, e.q);
      std::cout << "  " << e.p << " - " << e.q << '\n';
      ++connections;
    }
  }

  std::cout << "\nProcessed " << pairs.size() << " pairs over " << n
            << " objects; " << connections << " were connecting.\n";
  return 0;
}
