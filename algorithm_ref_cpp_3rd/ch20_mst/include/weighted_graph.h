#ifndef ALG_REF_CH20_WEIGHTED_GRAPH_H_
#define ALG_REF_CH20_WEIGHTED_GRAPH_H_

// Chapter 20: Minimum Spanning Trees -- the weighted-edge graph type.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 20.
// The original code used templated GRAPH classes holding raw Edge* pointers
// and hand-written adjacency iterators.  Here an Edge is a small value type
// carrying a double weight, and WeightedGraph stores an adjacency list of
// Edge values in std::vector.  A range-style begin()/end() over adj(v)
// replaces the original adjIterator.
//
// Complexity (V vertices, E edges), adjacency-list representation:
//   insert edge       O(1)
//   iterate adj(v)    O(deg(v))
//   space             O(V + E)

#include <vector>

namespace ch20 {

// A weighted, undirected edge between vertices v and w.
struct Edge {
  int v = -1;
  int w = -1;
  double weight = 0.0;

  Edge() = default;
  Edge(int v, int w, double weight) : v(v), w(w), weight(weight) {}

  // Given one endpoint, return the other (supports undirected traversal).
  int other(int x) const { return x == v ? w : v; }
};

// Undirected graph with weighted edges, stored as an adjacency list.
class WeightedGraph {
 public:
  explicit WeightedGraph(int vertices)
      : adj_(vertices), edge_count_(0) {}

  int V() const { return static_cast<int>(adj_.size()); }
  int E() const { return edge_count_; }

  // Insert an undirected edge; the same Edge is recorded on both endpoints.
  void insert(const Edge& e) {
    adj_[e.v].push_back(e);
    adj_[e.w].push_back(e);
    ++edge_count_;
  }

  void insert(int v, int w, double weight) { insert(Edge(v, w, weight)); }

  // Edges incident to v (each undirected edge appears once per endpoint).
  const std::vector<Edge>& adj(int v) const { return adj_[v]; }

  // Every edge exactly once, useful for edge-oriented algorithms (Kruskal).
  std::vector<Edge> edges() const {
    std::vector<Edge> result;
    result.reserve(edge_count_);
    for (int v = 0; v < V(); ++v)
      for (const Edge& e : adj_[v])
        if (e.v == v) result.push_back(e);  // emit once, from lower-listed end
    return result;
  }

 private:
  std::vector<std::vector<Edge>> adj_;
  int edge_count_;
};

}  // namespace ch20

#endif  // ALG_REF_CH20_WEIGHTED_GRAPH_H_
