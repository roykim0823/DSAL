#ifndef ALG_REF_CH17_GRAPH_H_
#define ALG_REF_CH17_GRAPH_H_

// Chapter 17: Graph Properties and Types.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 17.
// Two interchangeable graph representations share Sedgewick's ADT interface so
// client code can be written once and run against either:
//
//   V()            -- number of vertices
//   E()            -- number of edges
//   directed()     -- is the graph directed?
//   insert(Edge)   -- add an edge
//   remove(Edge)   -- delete an edge
//   edge(v, w)     -- is there an edge from v to w?
//   adjIterator    -- iterate the neighbors of a vertex via beg()/nxt()/end()
//
//   DenseGRAPH  -- adjacency matrix   (edge test O(1),   space O(V^2))
//   SparseGRAPH -- adjacency list     (edge test O(V),   space O(V + E))
//
// The adjIterator is the key to representation independence: templated clients
// walk neighbors through `typename Graph::adjIterator` without knowing which
// representation backs the graph.  The original used raw C linked lists; here
// the sparse form is held in std::vector, keeping the same iterator surface.

#include <vector>

namespace ch17 {

// A graph edge between vertices v and w.
struct Edge {
  int v, w;
  Edge(int v = -1, int w = -1) : v(v), w(w) {}
};

// Adjacency-matrix representation: adj[v][w] records whether edge v-w exists.
class DenseGRAPH {
 public:
  DenseGRAPH(int V, bool digraph = false)
      : Vcnt_(V), Ecnt_(0), digraph_(digraph), adj_(V, std::vector<bool>(V, false)) {}

  int V() const { return Vcnt_; }
  int E() const { return Ecnt_; }
  bool directed() const { return digraph_; }

  void insert(Edge e) {
    int v = e.v, w = e.w;
    if (!adj_[v][w]) Ecnt_++;
    adj_[v][w] = true;
    if (!digraph_) adj_[w][v] = true;
  }

  void remove(Edge e) {
    int v = e.v, w = e.w;
    if (adj_[v][w]) Ecnt_--;
    adj_[v][w] = false;
    if (!digraph_) adj_[w][v] = false;
  }

  bool edge(int v, int w) const { return adj_[v][w]; }

  class adjIterator;
  friend class adjIterator;

 private:
  int Vcnt_, Ecnt_;
  bool digraph_;
  std::vector<std::vector<bool>> adj_;
};

// Scans row v of the matrix for the next set entry.
class DenseGRAPH::adjIterator {
 public:
  adjIterator(const DenseGRAPH& G, int v) : G_(G), i_(-1), v_(v) {}

  int beg() {
    i_ = -1;
    return nxt();
  }

  int nxt() {
    for (i_++; i_ < G_.V(); i_++)
      if (G_.adj_[v_][i_]) return i_;
    return -1;
  }

  bool end() const { return i_ >= G_.V(); }

 private:
  const DenseGRAPH& G_;
  int i_, v_;
};

// Adjacency-list representation: adj[v] holds the neighbors of v.
class SparseGRAPH {
 public:
  SparseGRAPH(int V, bool digraph = false)
      : Vcnt_(V), Ecnt_(0), digraph_(digraph), adj_(V) {}

  int V() const { return Vcnt_; }
  int E() const { return Ecnt_; }
  bool directed() const { return digraph_; }

  void insert(Edge e) {
    int v = e.v, w = e.w;
    adj_[v].push_back(w);
    if (!digraph_) adj_[w].push_back(v);
    Ecnt_++;
  }

  void remove(Edge e) {
    int v = e.v, w = e.w;
    removeOne(v, w);
    if (!digraph_) removeOne(w, v);
    Ecnt_--;
  }

  bool edge(int v, int w) const {
    for (int t : adj_[v])
      if (t == w) return true;
    return false;
  }

  class adjIterator;
  friend class adjIterator;

 private:
  void removeOne(int v, int w) {
    for (std::size_t i = 0; i < adj_[v].size(); i++)
      if (adj_[v][i] == w) {
        adj_[v].erase(adj_[v].begin() + i);
        return;
      }
  }

  int Vcnt_, Ecnt_;
  bool digraph_;
  std::vector<std::vector<int>> adj_;
};

// Walks vertex v's neighbor list by index.
class SparseGRAPH::adjIterator {
 public:
  adjIterator(const SparseGRAPH& G, int v) : G_(G), v_(v), i_(0) {}

  int beg() {
    i_ = 0;
    return end() ? -1 : G_.adj_[v_][i_];
  }

  int nxt() {
    i_++;
    return end() ? -1 : G_.adj_[v_][i_];
  }

  bool end() const { return i_ >= static_cast<int>(G_.adj_[v_].size()); }

 private:
  const SparseGRAPH& G_;
  int v_, i_;
};

}  // namespace ch17

#endif  // ALG_REF_CH17_GRAPH_H_
