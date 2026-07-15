#ifndef ALG_REF_CH21_WEIGHTED_DIGRAPH_H_
#define ALG_REF_CH21_WEIGHTED_DIGRAPH_H_

// Chapter 21: Shortest Paths -- a self-contained weighted directed graph.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 21.
// The original used templated Graph/Edge classes with adjacency iterators;
// here the digraph owns its edges in an adjacency-list representation and
// exposes a small, direct interface used by the shortest-path solvers.
//
// Edges carry a non-negative double weight (required by Dijkstra).

#include <vector>

namespace ch21 {

// A directed, weighted edge: from -> to with a real-valued weight.
struct Edge {
  int from;
  int to;
  double weight;
};

// Weighted digraph stored as adjacency lists.
//   V()          -- number of vertices
//   insert(e)    -- add a directed edge
//   adj(v)       -- edges leaving v
class WeightedDigraph {
 public:
  explicit WeightedDigraph(int v) : adj_(v) {}

  int V() const { return static_cast<int>(adj_.size()); }

  void insert(const Edge& e) { adj_[e.from].push_back(e); }

  void insert(int from, int to, double weight) {
    insert(Edge{from, to, weight});
  }

  const std::vector<Edge>& adj(int v) const { return adj_[v]; }

 private:
  std::vector<std::vector<Edge>> adj_;
};

}  // namespace ch21

#endif  // ALG_REF_CH21_WEIGHTED_DIGRAPH_H_
