#ifndef ALG_REF_CH20_MST_H_
#define ALG_REF_CH20_MST_H_

// Chapter 20: Minimum Spanning Trees -- Prim and Kruskal.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 20.
// Both algorithms return the same result: the list of edges forming a
// minimum spanning tree of a connected, weighted, undirected graph.
//
// Prim   grows one tree, repeatedly adding the cheapest edge leaving it.
//        This simple version scans all fringe vertices each step.
//        Complexity O(V^2).
// Kruskal considers edges in weight order, adding an edge whenever it joins
//        two distinct components (tracked with union-find).
//        Complexity O(E log E) dominated by the sort.

#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

#include "weighted_graph.h"

namespace ch20 {

// Result of an MST computation: the chosen edges and their total weight.
struct MstResult {
  std::vector<Edge> edges;
  double weight = 0.0;
};

// Prim's algorithm (dense O(V^2) variant), starting from vertex 0.
inline MstResult Prim(const WeightedGraph& g) {
  const int n = g.V();
  const double kInf = std::numeric_limits<double>::max();

  std::vector<bool> in_tree(n, false);  // vertex already in the MST?
  std::vector<double> dist(n, kInf);    // cheapest known edge to the tree
  std::vector<Edge> from(n);            // that cheapest edge itself

  MstResult result;
  if (n == 0) return result;
  dist[0] = 0.0;

  for (int i = 0; i < n; ++i) {
    // Pick the non-tree vertex closest to the current tree.
    int min = -1;
    for (int v = 0; v < n; ++v)
      if (!in_tree[v] && (min == -1 || dist[v] < dist[min])) min = v;
    if (min == -1 || dist[min] == kInf) break;  // graph is disconnected

    in_tree[min] = true;
    if (min != 0) {  // vertex 0 is the seed and has no incoming tree edge
      result.edges.push_back(from[min]);
      result.weight += from[min].weight;
    }

    // Relax edges leaving the newly added vertex.
    for (const Edge& e : g.adj(min)) {
      int w = e.other(min);
      if (!in_tree[w] && e.weight < dist[w]) {
        dist[w] = e.weight;
        from[w] = e;
      }
    }
  }
  return result;
}

// Union-find with weighting + path compression, used by Kruskal.
class UnionFind {
 public:
  explicit UnionFind(int n) : id_(n), sz_(n, 1) {
    std::iota(id_.begin(), id_.end(), 0);
  }

  int find(int i) {
    while (i != id_[i]) {
      id_[i] = id_[id_[i]];  // path compression
      i = id_[i];
    }
    return i;
  }

  bool connected(int p, int q) { return find(p) == find(q); }

  void unite(int p, int q) {
    int i = find(p), j = find(q);
    if (i == j) return;
    if (sz_[i] < sz_[j]) {
      id_[i] = j;
      sz_[j] += sz_[i];
    } else {
      id_[j] = i;
      sz_[i] += sz_[j];
    }
  }

 private:
  std::vector<int> id_;
  std::vector<int> sz_;
};

// Kruskal's algorithm: sort edges by weight, add those that join components.
inline MstResult Kruskal(const WeightedGraph& g) {
  MstResult result;
  std::vector<Edge> edges = g.edges();
  std::sort(edges.begin(), edges.end(),
            [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

  UnionFind uf(g.V());
  for (const Edge& e : edges) {
    if (static_cast<int>(result.edges.size()) == g.V() - 1) break;
    if (!uf.connected(e.v, e.w)) {
      uf.unite(e.v, e.w);
      result.edges.push_back(e);
      result.weight += e.weight;
    }
  }
  return result;
}

}  // namespace ch20

#endif  // ALG_REF_CH20_MST_H_
