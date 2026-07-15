#ifndef ALG_REF_CH19_STRONG_COMPONENTS_H_
#define ALG_REF_CH19_STRONG_COMPONENTS_H_

// Chapter 19: strong components via Kosaraju's two-pass algorithm.
//
// Two vertices are strongly connected if each is reachable from the other.
// Kosaraju:
//   1. DFS the reverse of G, recording vertices in postorder.
//   2. DFS G in reverse-postorder; each DFS tree is one strong component.
//
// Exposes:
//   count()               -> number of strong components
//   id(v)                 -> component identifier of vertex v
//   stronglyReachable(v,w)-> do v and w share a component?
//
// Complexity: O(V + E) time.

#include <vector>

#include "digraph.h"

namespace ch19 {

template <class Graph>
class StrongComponents {
 public:
  explicit StrongComponents(const Graph& G)
      : G_(G), cnt_(0), scnt_(0), post_(G.V()), id_(G.V(), -1) {
    // Pass 1: postorder of a DFS on the reversed digraph.
    Graph R(G.V());
    reverse(G, R);
    for (int v = 0; v < R.V(); ++v)
      if (id_[v] == -1) dfsR(R, v);

    std::vector<int> post_reverse = post_;

    // Pass 2: DFS G in decreasing reverse-postorder; one tree == one component.
    cnt_ = 0;
    id_.assign(G_.V(), -1);
    for (int v = G_.V() - 1; v >= 0; --v)
      if (id_[post_reverse[v]] == -1) {
        dfsR(G_, post_reverse[v]);
        ++scnt_;
      }
  }

  int count() const { return scnt_; }
  int id(int v) const { return id_[v]; }
  bool stronglyReachable(int v, int w) const { return id_[v] == id_[w]; }

 private:
  void dfsR(const Graph& G, int w) {
    id_[w] = scnt_;
    typename Graph::adjIterator A(G, w);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      if (id_[t] == -1) dfsR(G, t);
    post_[cnt_++] = w;
  }

  const Graph& G_;
  int cnt_, scnt_;
  std::vector<int> post_, id_;
};

}  // namespace ch19

#endif  // ALG_REF_CH19_STRONG_COMPONENTS_H_
