#ifndef ALG_REF_CH18_GRAPH_H_
#define ALG_REF_CH18_GRAPH_H_

// Chapter 18: Graph Search -- self-contained graph representation.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapters 17-18.
// The original code split the ADT (GRAPH) from concrete adjacency-matrix /
// adjacency-list implementations; here a single adjacency-list Graph provides
// the interface the search algorithms depend on:
//
//   V()            -- number of vertices
//   E()            -- number of edges
//   directed()     -- is the graph directed?
//   insert(Edge)   -- add an edge
//   edge(v, w)     -- is there an edge v->w?
//   adjIterator    -- iterate the neighbours of a vertex
//
// The adjIterator follows Sedgewick's beg()/nxt()/end() protocol so the
// templated search classes remain implementation-independent.
//
// Complexity (V vertices, E edges): adjacency list uses O(V + E) space;
// iterating all neighbours of a vertex is O(degree).

#include <vector>

namespace ch18 {

// An edge between vertices v and w.
struct Edge {
  int v, w;
  Edge(int v = -1, int w = -1) : v(v), w(w) {}
};

// Undirected/directed graph stored as adjacency lists.
class Graph {
 public:
  explicit Graph(int V, bool digraph = false)
      : adj_(V), v_cnt_(V), e_cnt_(0), digraph_(digraph) {}

  int V() const { return v_cnt_; }
  int E() const { return e_cnt_; }
  bool directed() const { return digraph_; }

  void insert(Edge e) {
    adj_[e.v].push_back(e.w);
    if (!digraph_) adj_[e.w].push_back(e.v);
    ++e_cnt_;
  }

  bool edge(int v, int w) const {
    for (int t : adj_[v])
      if (t == w) return true;
    return false;
  }

  // Iterates the vertices adjacent to a given vertex v.
  class adjIterator {
   public:
    adjIterator(const Graph& G, int v) : adj_(G.adj_[v]), i_(0) {}
    int beg() {
      i_ = 0;
      return end() ? -1 : adj_[i_];
    }
    int nxt() {
      ++i_;
      return end() ? -1 : adj_[i_];
    }
    bool end() const { return i_ >= static_cast<int>(adj_.size()); }

   private:
    const std::vector<int>& adj_;
    int i_;
  };
  friend class adjIterator;

 private:
  std::vector<std::vector<int>> adj_;
  int v_cnt_, e_cnt_;
  bool digraph_;
};

}  // namespace ch18

#endif  // ALG_REF_CH18_GRAPH_H_
