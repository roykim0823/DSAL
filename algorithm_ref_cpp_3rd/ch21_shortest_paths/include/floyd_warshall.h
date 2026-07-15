#ifndef ALG_REF_CH21_FLOYD_WARSHALL_H_
#define ALG_REF_CH21_FLOYD_WARSHALL_H_

// Chapter 21: Shortest Paths -- Floyd-Warshall all-pairs shortest paths.
//
// Computes shortest-path distances between every pair of vertices by
// progressively allowing paths through each vertex as an intermediate.
// Works for any digraph without negative cycles.
//
// Complexity: O(V^3) time, O(V^2) space.

#include <limits>
#include <vector>

#include "weighted_digraph.h"

namespace ch21 {

class FloydWarshall {
 public:
  static double Infinity() { return std::numeric_limits<double>::infinity(); }

  explicit FloydWarshall(const WeightedDigraph& g)
      : dist_(g.V(), std::vector<double>(g.V(), Infinity())) {
    const int n = g.V();
    for (int v = 0; v < n; ++v) dist_[v][v] = 0.0;
    for (int v = 0; v < n; ++v)
      for (const Edge& e : g.adj(v))
        if (e.weight < dist_[e.from][e.to]) dist_[e.from][e.to] = e.weight;

    for (int k = 0; k < n; ++k)
      for (int s = 0; s < n; ++s) {
        if (dist_[s][k] == Infinity()) continue;
        for (int t = 0; t < n; ++t) {
          double through = dist_[s][k] + dist_[k][t];
          if (through < dist_[s][t]) dist_[s][t] = through;
        }
      }
  }

  // Shortest-path distance from s to t (kInfinity if unreachable).
  double dist(int s, int t) const { return dist_[s][t]; }

  int V() const { return static_cast<int>(dist_.size()); }

 private:
  std::vector<std::vector<double>> dist_;
};

}  // namespace ch21

#endif  // ALG_REF_CH21_FLOYD_WARSHALL_H_
