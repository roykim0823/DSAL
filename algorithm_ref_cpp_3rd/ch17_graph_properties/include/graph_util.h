#ifndef ALG_REF_CH17_GRAPH_UTIL_H_
#define ALG_REF_CH17_GRAPH_UTIL_H_

// Representation-independent graph clients (Sedgewick, Chapter 17).
//
// Each of these is templated on the Graph type and touches the graph only
// through the shared ADT interface -- crucially the `adjIterator` -- so the
// same code works for DenseGRAPH, SparseGRAPH, or any future representation.

#include <iomanip>
#include <iostream>
#include <vector>

#include "graph.h"

namespace ch17 {

// Collect every edge of G.  For undirected graphs each edge is reported once
// (only when v < w) to avoid the two mirrored adjacency entries.
template <class Graph>
std::vector<Edge> edges(const Graph& G) {
  std::vector<Edge> a;
  a.reserve(G.E());
  for (int v = 0; v < G.V(); v++) {
    typename Graph::adjIterator A(G, v);
    for (int w = A.beg(); !A.end(); w = A.nxt())
      if (G.directed() || v < w) a.push_back(Edge(v, w));
  }
  return a;
}

// Print the adjacency list of every vertex.
template <class Graph>
void show(const Graph& G) {
  for (int s = 0; s < G.V(); s++) {
    std::cout << std::setw(2) << s << ":";
    typename Graph::adjIterator A(G, s);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      std::cout << std::setw(3) << t;
    std::cout << '\n';
  }
}

// Precompute the degree (neighbor count) of each vertex.
template <class Graph>
class DEGREE {
 public:
  explicit DEGREE(const Graph& G) : degree_(G.V(), 0) {
    for (int v = 0; v < G.V(); v++) {
      typename Graph::adjIterator A(G, v);
      for (A.beg(); !A.end(); A.nxt()) degree_[v]++;
    }
  }

  int operator[](int v) const { return degree_[v]; }

 private:
  std::vector<int> degree_;
};

}  // namespace ch17

#endif  // ALG_REF_CH17_GRAPH_UTIL_H_
