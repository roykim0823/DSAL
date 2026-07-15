#ifndef ALG_REF_CH19_TRANSITIVE_CLOSURE_H_
#define ALG_REF_CH19_TRANSITIVE_CLOSURE_H_

// Chapter 19: transitive closure of a digraph.
//
// reachable(s, t) is true iff there is a directed path s -> ... -> t.
// The closure matrix is boolean V x V, with the diagonal set (a vertex
// reaches itself by the empty path).
//
// TransitiveClosure uses Warshall's algorithm: for each intermediate vertex i,
// if s reaches i and i reaches t, then s reaches t.
//
// Complexity: O(V^3) time, O(V^2) space.

#include <vector>

namespace ch19 {

template <class Graph>
class TransitiveClosure {
 public:
  explicit TransitiveClosure(const Graph& G)
      : reach_(G.V(), std::vector<bool>(G.V(), false)) {
    int V = G.V();
    // Seed with the digraph's own edges plus reflexive self-loops.
    for (int s = 0; s < V; ++s) {
      reach_[s][s] = true;
      typename Graph::adjIterator A(G, s);
      for (int t = A.beg(); !A.end(); t = A.nxt()) reach_[s][t] = true;
    }
    // Warshall: close over every possible intermediate vertex i.
    for (int i = 0; i < V; ++i)
      for (int s = 0; s < V; ++s)
        if (reach_[s][i])
          for (int t = 0; t < V; ++t)
            if (reach_[i][t]) reach_[s][t] = true;
  }

  bool reachable(int s, int t) const { return reach_[s][t]; }

 private:
  std::vector<std::vector<bool>> reach_;
};

}  // namespace ch19

#endif  // ALG_REF_CH19_TRANSITIVE_CLOSURE_H_
