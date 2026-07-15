#ifndef ALG_REF_CH05_BINARY_TREE_H_
#define ALG_REF_CH05_BINARY_TREE_H_

// Chapter 5: Recursion and Trees -- a binary tree and its traversals.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 5.
// The original used `node*` with `new`/manual delete; here ownership is held by
// std::unique_ptr so the tree is freed automatically.  Traversals are provided
// both recursively (preorder) and iteratively (stack-based preorder and
// queue-based level order), matching the three programs in the text.
//
// Complexity (N nodes, h height):
//   Count / Height / all traversals   O(N) time
//   recursion / explicit stack        O(h) auxiliary space
//   level order                       O(N) auxiliary space (queue)

#include <memory>
#include <queue>
#include <stack>
#include <vector>

namespace ch05 {

struct Node {
  int item;
  std::unique_ptr<Node> l;
  std::unique_ptr<Node> r;
  explicit Node(int x) : item(x) {}
};

using NodePtr = std::unique_ptr<Node>;

inline NodePtr MakeNode(int x) { return std::unique_ptr<Node>(new Node(x)); }

// Number of nodes in the tree rooted at h.
inline int Count(const Node* h) {
  if (h == nullptr) return 0;
  return Count(h->l.get()) + Count(h->r.get()) + 1;
}

// Height of the tree (empty tree == -1, single node == 0).
inline int Height(const Node* h) {
  if (h == nullptr) return -1;
  int u = Height(h->l.get());
  int v = Height(h->r.get());
  return (u > v ? u : v) + 1;
}

// Recursive preorder traversal: visit node, then left, then right.
inline void PreorderRecursive(const Node* h, std::vector<int>& out) {
  if (h == nullptr) return;
  out.push_back(h->item);
  PreorderRecursive(h->l.get(), out);
  PreorderRecursive(h->r.get(), out);
}

// Stack-based preorder traversal (right pushed first so left is visited first).
inline std::vector<int> PreorderStack(const Node* h) {
  std::vector<int> out;
  if (h == nullptr) return out;
  std::stack<const Node*> s;
  s.push(h);
  while (!s.empty()) {
    const Node* x = s.top();
    s.pop();
    out.push_back(x->item);
    if (x->r) s.push(x->r.get());
    if (x->l) s.push(x->l.get());
  }
  return out;
}

// Queue-based level-order (breadth-first) traversal.
inline std::vector<int> LevelOrder(const Node* h) {
  std::vector<int> out;
  if (h == nullptr) return out;
  std::queue<const Node*> q;
  q.push(h);
  while (!q.empty()) {
    const Node* x = q.front();
    q.pop();
    out.push_back(x->item);
    if (x->l) q.push(x->l.get());
    if (x->r) q.push(x->r.get());
  }
  return out;
}

}  // namespace ch05

#endif  // ALG_REF_CH05_BINARY_TREE_H_
