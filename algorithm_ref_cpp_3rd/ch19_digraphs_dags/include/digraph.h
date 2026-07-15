#ifndef ALG_REF_CH19_DIGRAPH_H_
#define ALG_REF_CH19_DIGRAPH_H_

// Chapter 19: Digraphs and DAGs -- a self-contained directed graph type.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapters 17 & 19.
// The original code split the graph interface (GRAPH/adjIterator) into a
// separate translation unit; here everything lives in this header.
//
// Digraph stores an adjacency list per vertex (std::vector<std::vector<int>>).
// Directed edge v->w is recorded in adj_[v].  adjIterator walks a vertex's
// out-neighbours, matching the beg()/nxt()/end() interface the algorithms use.
//
// Complexity (V vertices, E edges):
//   insert(Edge)       O(1) amortized
//   edge(v, w)         O(out-degree of v)
//   iterate a vertex   O(out-degree of v)
//   reverse(G, R)      O(V + E)

#include <vector>

namespace ch19 {

// A directed edge v -> w.
struct Edge {
  int v, w;
  Edge(int v = -1, int w = -1) : v(v), w(w) {}
};

// Directed graph backed by adjacency lists.
class Digraph {
 public:
  explicit Digraph(int V) : v_count_(V), e_count_(0), adj_(V) {}

  int V() const { return v_count_; }
  int E() const { return e_count_; }
  bool directed() const { return true; }

  // Insert directed edge e.v -> e.w (no duplicate check; parallel edges kept).
  void insert(Edge e) {
    adj_[e.v].push_back(e.w);
    ++e_count_;
  }

  // Is there an edge v -> w?
  bool edge(int v, int w) const {
    for (int t : adj_[v])
      if (t == w) return true;
    return false;
  }

  // Iterates the out-neighbours of a fixed vertex v.
  class adjIterator {
   public:
    adjIterator(const Digraph& G, int v) : adj_(G.adj_[v]), i_(0) {}

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
  int v_count_;
  int e_count_;
  std::vector<std::vector<int>> adj_;
};

// Build R as the reverse of G: every edge v -> w becomes w -> v.  O(V + E).
template <class inGraph, class outGraph>
void reverse(const inGraph& G, outGraph& R) {
  for (int v = 0; v < G.V(); ++v) {
    typename inGraph::adjIterator A(G, v);
    for (int w = A.beg(); !A.end(); w = A.nxt())
      R.insert(Edge(w, v));
  }
}

}  // namespace ch19

#endif  // ALG_REF_CH19_DIGRAPH_H_
