#ifndef ALG_REF_CH19_TOPOLOGICAL_SORT_H_
#define ALG_REF_CH19_TOPOLOGICAL_SORT_H_

// Chapter 19: topological sort of a DAG.
//
// Two classic strategies, each producing a linear ordering of the vertices
// such that every edge points from an earlier vertex to a later one:
//
//   TopoSortDFS    reverse-postorder of a depth-first search.
//   TopoSortKahn   repeatedly emit a source (in-degree 0), removing its edges.
//
// Both expose:
//   order(i)   -> the vertex placed at rank i (topological order)
//   rank(v)    -> the rank assigned to vertex v (inverse of order)
//   valid()    -> false if the digraph had a cycle (Kahn only; DFS assumes DAG)
//
// Complexity: O(V + E) for both.

#include <vector>

namespace ch19 {

// Reverse-postorder DFS topological sort (Sedgewick's dagTS).
template <class Dag>
class TopoSortDFS {
 public:
  explicit TopoSortDFS(const Dag& D)
      : D_(D), cnt_(0), tcnt_(0), pre_(D.V(), -1), order_(D.V(), -1),
        rank_(D.V(), -1) {
    for (int v = 0; v < D_.V(); ++v)
      if (pre_[v] == -1) tsR(v);
  }

  int order(int i) const { return order_[i]; }
  int rank(int v) const { return rank_[v]; }
  bool valid() const { return true; }  // assumes input is a DAG

 private:
  void tsR(int v) {
    pre_[v] = cnt_++;
    typename Dag::adjIterator A(D_, v);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      if (pre_[t] == -1) tsR(t);
    // Postorder append, then reverse via descending rank indexing.
    rank_[v] = tcnt_;
    order_[tcnt_++] = v;
  }

  const Dag& D_;
  int cnt_, tcnt_;
  std::vector<int> pre_, order_, rank_;
};

// Source-queue (Kahn's) topological sort.  Also detects cycles.
template <class Dag>
class TopoSortKahn {
 public:
  explicit TopoSortKahn(const Dag& D)
      : D_(D), order_(D.V(), -1), rank_(D.V(), -1), valid_(false) {
    std::vector<int> indeg(D_.V(), 0);
    for (int v = 0; v < D_.V(); ++v) {
      typename Dag::adjIterator A(D_, v);
      for (int t = A.beg(); !A.end(); t = A.nxt()) ++indeg[t];
    }

    std::vector<int> queue;  // FIFO of current sources
    std::size_t head = 0;
    for (int v = 0; v < D_.V(); ++v)
      if (indeg[v] == 0) queue.push_back(v);

    int j = 0;
    while (head < queue.size()) {
      int v = queue[head++];
      order_[j] = v;
      rank_[v] = j;
      ++j;
      typename Dag::adjIterator A(D_, v);
      for (int t = A.beg(); !A.end(); t = A.nxt())
        if (--indeg[t] == 0) queue.push_back(t);
    }
    valid_ = (j == D_.V());  // all vertices emitted => acyclic
  }

  int order(int i) const { return order_[i]; }
  int rank(int v) const { return rank_[v]; }
  bool valid() const { return valid_; }

 private:
  const Dag& D_;
  std::vector<int> order_, rank_;
  bool valid_;
};

}  // namespace ch19

#endif  // ALG_REF_CH19_TOPOLOGICAL_SORT_H_
