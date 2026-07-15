// Chapter 21 driver: shortest paths on a weighted directed graph.
//
// No arguments required -- builds a fixed sample weighted digraph, then:
//   1. runs Dijkstra from vertex 0 and prints single-source distances,
//   2. runs Floyd-Warshall and prints the all-pairs distance matrix.
// Row 0 of the matrix must agree with the Dijkstra distances.
//
//   ./ch21_shortest_paths_main
//
// Sample digraph (from Sedgewick, Chapter 21), 6 vertices:
//   0->1 .41  0->5 .29  1->2 .51  1->4 .32  2->3 .50
//   3->0 .45  3->5 .38  4->2 .32  4->3 .36  5->1 .29  5->4 .21

#include <iomanip>
#include <iostream>
#include <limits>

#include "dijkstra.h"
#include "floyd_warshall.h"
#include "weighted_digraph.h"

using ch21::Dijkstra;
using ch21::FloydWarshall;
using ch21::WeightedDigraph;

namespace {

void PrintDist(double d) {
  if (d == std::numeric_limits<double>::infinity()) {
    std::cout << std::setw(6) << "inf";
  } else {
    std::cout << std::setw(6) << std::fixed << std::setprecision(2) << d;
  }
}

}  // namespace

int main() {
  const int kV = 6;
  WeightedDigraph g(kV);
  g.insert(0, 1, 0.41);
  g.insert(0, 5, 0.29);
  g.insert(1, 2, 0.51);
  g.insert(1, 4, 0.32);
  g.insert(2, 3, 0.50);
  g.insert(3, 0, 0.45);
  g.insert(3, 5, 0.38);
  g.insert(4, 2, 0.32);
  g.insert(4, 3, 0.36);
  g.insert(5, 1, 0.29);
  g.insert(5, 4, 0.21);

  const int kSource = 0;
  Dijkstra spt(g, kSource);
  std::cout << "Dijkstra single-source shortest paths from vertex " << kSource
            << ":\n";
  for (int v = 0; v < g.V(); ++v) {
    std::cout << "  " << kSource << " -> " << v << "  dist =";
    PrintDist(spt.dist(v));
    std::cout << "  (parent " << spt.parent(v) << ")\n";
  }

  FloydWarshall all(g);
  std::cout << "\nFloyd-Warshall all-pairs distance matrix:\n     ";
  for (int t = 0; t < all.V(); ++t) std::cout << std::setw(6) << t;
  std::cout << '\n';
  for (int s = 0; s < all.V(); ++s) {
    std::cout << std::setw(4) << s << ' ';
    for (int t = 0; t < all.V(); ++t) PrintDist(all.dist(s, t));
    std::cout << '\n';
  }

  return 0;
}
