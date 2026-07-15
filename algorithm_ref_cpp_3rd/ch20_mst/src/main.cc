// Chapter 20 driver: build a fixed weighted undirected graph and compute its
// minimum spanning tree two ways -- Prim and Kruskal.  Both report the same
// total weight; only the discovery order of the edges differs.
//
//   ./ch20_mst_main    # runs the built-in sample, no arguments needed

#include <iomanip>
#include <iostream>

#include "mst.h"
#include "weighted_graph.h"

using ch20::Edge;
using ch20::Kruskal;
using ch20::MstResult;
using ch20::Prim;
using ch20::WeightedGraph;

namespace {

// Sedgewick's 8-vertex weighted-graph example (Chapter 20).
WeightedGraph BuildSample() {
  WeightedGraph g(8);
  g.insert(0, 1, 0.32);
  g.insert(0, 2, 0.29);
  g.insert(0, 5, 0.60);
  g.insert(0, 6, 0.51);
  g.insert(0, 7, 0.31);
  g.insert(1, 7, 0.21);
  g.insert(3, 4, 0.34);
  g.insert(3, 5, 0.18);
  g.insert(4, 5, 0.40);
  g.insert(4, 6, 0.51);
  g.insert(4, 7, 0.46);
  g.insert(6, 7, 0.25);
  return g;
}

void Report(const char* name, const MstResult& mst) {
  std::cout << name << " MST edges:\n";
  for (const Edge& e : mst.edges)
    std::cout << "  " << e.v << " - " << e.w << "  " << std::fixed
              << std::setprecision(2) << e.weight << '\n';
  std::cout << "  total weight = " << std::fixed << std::setprecision(2)
            << mst.weight << "\n\n";
}

}  // namespace

int main() {
  WeightedGraph g = BuildSample();
  std::cout << "Weighted undirected graph: " << g.V() << " vertices, " << g.E()
            << " edges.\n\n";

  Report("Prim", Prim(g));
  Report("Kruskal", Kruskal(g));
  return 0;
}
