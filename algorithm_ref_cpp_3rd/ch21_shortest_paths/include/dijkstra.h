#ifndef ALG_REF_CH21_DIJKSTRA_H_
#define ALG_REF_CH21_DIJKSTRA_H_

// Chapter 21: Shortest Paths -- Dijkstra's single-source shortest paths.
//
// Builds a shortest-path tree (SPT) rooted at a source vertex using a
// priority queue keyed on the current tentative distance.  Requires all
// edge weights to be non-negative.
//
// Complexity with a binary-heap priority queue: O(E log V).

#include <limits>
#include <queue>
#include <vector>

#include "weighted_digraph.h"

namespace ch21 {

class Dijkstra {
 public:
  static double Infinity() { return std::numeric_limits<double>::infinity(); }

  Dijkstra(const WeightedDigraph& g, int source)
      : dist_(g.V(), Infinity()), parent_(g.V(), -1) {
    // Min-heap of (distance, vertex) pairs; smallest distance on top.
    using Entry = std::pair<double, int>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> pq;

    dist_[source] = 0.0;
    pq.push({0.0, source});

    while (!pq.empty()) {
      double d = pq.top().first;
      int v = pq.top().second;
      pq.pop();
      // Skip stale heap entries (a shorter distance was already settled).
      if (d > dist_[v]) continue;

      for (const Edge& e : g.adj(v)) {
        double relaxed = dist_[v] + e.weight;
        if (relaxed < dist_[e.to]) {
          dist_[e.to] = relaxed;
          parent_[e.to] = v;
          pq.push({relaxed, e.to});
        }
      }
    }
  }

  // Shortest-path distance from the source to v (kInfinity if unreachable).
  double dist(int v) const { return dist_[v]; }

  // Predecessor of v on the shortest-path tree (-1 for source/unreachable).
  int parent(int v) const { return parent_[v]; }

 private:
  std::vector<double> dist_;
  std::vector<int> parent_;
};

}  // namespace ch21

#endif  // ALG_REF_CH21_DIJKSTRA_H_
