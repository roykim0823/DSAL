#ifndef ALG_REF_CH01_UNION_FIND_H_
#define ALG_REF_CH01_UNION_FIND_H_

// Chapter 1: Introduction -- the connectivity (union-find) problem.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 1.
// The original programs operated on raw C arrays; here the state is held in
// std::vector and each strategy is a small class exposing the same interface:
//
//   connected(p, q) -- are p and q in the same component?
//   unite(p, q)     -- merge the components containing p and q.
//
// Complexity (N objects, M union operations):
//   QuickFind            find O(1),      unite O(N)      -> O(M*N)
//   QuickUnion           find O(tree),   unite O(tree)
//   WeightedQuickUnion   find O(log N),  unite O(log N)
//   WeightedQuickUnionPC near-constant amortized (path compression)

#include <numeric>
#include <vector>

namespace ch01 {

// Eager approach: id[i] is the component identifier of i.
class QuickFind {
 public:
  explicit QuickFind(int n) : id_(n) { std::iota(id_.begin(), id_.end(), 0); }

  bool connected(int p, int q) const { return id_[p] == id_[q]; }

  void unite(int p, int q) {
    int pid = id_[p], qid = id_[q];
    if (pid == qid) return;
    for (int& x : id_)
      if (x == pid) x = qid;
  }

 private:
  std::vector<int> id_;
};

// Lazy approach: id[i] is the parent of i; a root is its own parent.
class QuickUnion {
 public:
  explicit QuickUnion(int n) : id_(n) { std::iota(id_.begin(), id_.end(), 0); }

  bool connected(int p, int q) { return root(p) == root(q); }

  void unite(int p, int q) {
    int i = root(p), j = root(q);
    if (i != j) id_[i] = j;
  }

 protected:
  int root(int i) {
    while (i != id_[i]) i = id_[i];
    return i;
  }
  std::vector<int> id_;
};

// Link the smaller tree beneath the larger one to keep trees flat.
class WeightedQuickUnion : public QuickUnion {
 public:
  explicit WeightedQuickUnion(int n) : QuickUnion(n), sz_(n, 1) {}

  void unite(int p, int q) {
    int i = root(p), j = root(q);
    if (i == j) return;
    if (sz_[i] < sz_[j]) {
      id_[i] = j;
      sz_[j] += sz_[i];
    } else {
      id_[j] = i;
      sz_[i] += sz_[j];
    }
  }

 protected:
  std::vector<int> sz_;
};

// Weighting plus path compression: flatten the tree on the way to the root.
class WeightedQuickUnionPC : public WeightedQuickUnion {
 public:
  explicit WeightedQuickUnionPC(int n) : WeightedQuickUnion(n) {}

 protected:
  int root(int i) {
    while (i != id_[i]) {
      id_[i] = id_[id_[i]];  // halve the path
      i = id_[i];
    }
    return i;
  }
};

}  // namespace ch01

#endif  // ALG_REF_CH01_UNION_FIND_H_
