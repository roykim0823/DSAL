#ifndef ALG_REF_CH18_GRAPH_SEARCH_H_
#define ALG_REF_CH18_GRAPH_SEARCH_H_

// Chapter 18: Graph Search -- depth-first and breadth-first search.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 18.
// Each algorithm is templated on a Graph exposing V() and a nested
// adjIterator with beg()/nxt()/end() (see graph.h).
//
// All searches visit every vertex and every edge, so with an adjacency-list
// graph they run in O(V + E) time and O(V) extra space.

#include <queue>
#include <vector>

namespace ch18 {

// Recursive depth-first search recording preorder (visit-order) numbers.
// ord[v] is the step at which v was first reached; count() is how many
// vertices were reached from the start vertex.
template <class Graph>
class DFS {
 public:
  explicit DFS(const Graph& G, int start = 0)
      : G_(G), cnt_(0), ord_(G.V(), -1) {
    // Explore the start vertex first, then any remaining components so that
    // every vertex receives a preorder number.
    search(start);
    for (int v = 0; v < G_.V(); ++v)
      if (ord_[v] == -1) search(v);
  }

  int count() const { return cnt_; }
  int operator[](int v) const { return ord_[v]; }

 private:
  void search(int v) {
    ord_[v] = cnt_++;
    typename Graph::adjIterator A(G_, v);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      if (ord_[t] == -1) search(t);
  }

  const Graph& G_;
  int cnt_;
  std::vector<int> ord_;
};

// Connected components via DFS: id[v] is the component index of v.
template <class Graph>
class CC {
 public:
  explicit CC(const Graph& G) : G_(G), ccnt_(0), id_(G.V(), -1) {
    for (int v = 0; v < G_.V(); ++v)
      if (id_[v] == -1) {
        search(v);
        ++ccnt_;
      }
  }

  int count() const { return ccnt_; }
  bool connect(int s, int t) const { return id_[s] == id_[t]; }
  int id(int v) const { return id_[v]; }

 private:
  void search(int w) {
    id_[w] = ccnt_;
    typename Graph::adjIterator A(G_, w);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      if (id_[t] == -1) search(t);
  }

  const Graph& G_;
  int ccnt_;
  std::vector<int> id_;
};

// Bipartiteness (two-colourability) via DFS two-colouring.
// color(v) is 0 or 1; bipartite() is false if any edge joins same-colour ends.
template <class Graph>
class BI {
 public:
  explicit BI(const Graph& G) : G_(G), ok_(true), vc_(G.V(), -1) {
    for (int v = 0; v < G_.V(); ++v)
      if (vc_[v] == -1)
        if (!dfs(v, 0)) {
          ok_ = false;
          return;
        }
  }

  bool bipartite() const { return ok_; }
  int color(int v) const { return vc_[v]; }

 private:
  bool dfs(int v, int c) {
    vc_[v] = (c + 1) % 2;
    typename Graph::adjIterator A(G_, v);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      if (vc_[t] == -1) {
        if (!dfs(t, vc_[v])) return false;
      } else if (vc_[t] != c) {
        return false;
      }
    return true;
  }

  const Graph& G_;
  bool ok_;
  std::vector<int> vc_;
};

// Breadth-first search from a source; ord[v] is the BFS visit order and
// st[v] is the parent (spanning-tree) link of v.
template <class Graph>
class BFS {
 public:
  BFS(const Graph& G, int source = 0)
      : G_(G), cnt_(0), ord_(G.V(), -1), st_(G.V(), -1) {
    search(Edge(source, source));
    for (int v = 0; v < G_.V(); ++v)
      if (ord_[v] == -1) search(Edge(v, v));
  }

  int count() const { return cnt_; }
  int operator[](int v) const { return ord_[v]; }
  int ST(int v) const { return st_[v]; }

 private:
  void search(Edge e) {
    std::queue<Edge> Q;
    Q.push(e);
    ord_[e.w] = cnt_++;
    while (!Q.empty()) {
      e = Q.front();
      Q.pop();
      st_[e.w] = e.v;
      typename Graph::adjIterator A(G_, e.w);
      for (int t = A.beg(); !A.end(); t = A.nxt())
        if (ord_[t] == -1) {
          Q.push(Edge(e.w, t));
          ord_[t] = cnt_++;
        }
    }
  }

  const Graph& G_;
  int cnt_;
  std::vector<int> ord_, st_;
};

}  // namespace ch18

#endif  // ALG_REF_CH18_GRAPH_SEARCH_H_
