#ifndef ALG_REF_CH13_SKIP_LIST_H_
#define ALG_REF_CH13_SKIP_LIST_H_

// Chapter 13: Balanced Trees -- skip-list symbol table (int keys).
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 13.  A
// skip list is a randomized structure: an ordered linked list augmented with
// extra forward links that skip over a geometrically decreasing fraction of
// the nodes, so a search can descend levels much like a balanced tree.
//
// The original used rand(); here a std::mt19937 (fixed seed for a
// deterministic demo) drives randX(), which picks each node's level.
//
// Interface:
//   insert(key) -- add a key.
//   contains(key) -- is key present?
//   inorder() -- keys in sorted order (walk the bottom level).
//
// Complexity (N keys, expected):
//   search  O(log N)
//   insert  O(log N)

#include <cstdint>
#include <random>
#include <vector>

namespace ch13 {

class SkipList {
 public:
  // seed fixes the level-choosing RNG so demo output is reproducible.
  explicit SkipList(std::uint32_t seed = 12345u)
      : head_(new Node(0, kMaxLevel)), lg_n_(0), rng_(seed) {}

  ~SkipList() {
    for (Node* x = head_; x != nullptr;) {
      Node* next = x->next[0];
      delete x;
      x = next;
    }
  }

  SkipList(const SkipList&) = delete;
  SkipList& operator=(const SkipList&) = delete;

  void insert(int key) { insertR(head_, new Node(key, randX()), lg_n_); }

  bool contains(int key) const { return searchR(head_, key, lg_n_); }

  // Keys in ascending order -- the bottom level is a sorted linked list.
  std::vector<int> inorder() const {
    std::vector<int> out;
    for (Node* x = head_->next[0]; x != nullptr; x = x->next[0])
      out.push_back(x->key);
    return out;
  }

 private:
  static const int kMaxLevel = 16;  // supports up to ~2^16 keys

  struct Node {
    int key;
    int sz;                      // number of forward links this node holds
    std::vector<Node*> next;     // forward links, index 0 = bottom level
    Node(int k, int levels) : key(k), sz(levels), next(levels, nullptr) {}
  };

  // Choose a level: level i survives with probability 1/2^i.
  int randX() {
    int i = 1;
    std::uniform_int_distribution<int> coin(0, 1);
    while (i < kMaxLevel && coin(rng_) == 0) ++i;
    if (i > lg_n_) lg_n_ = i;
    return i;
  }

  void insertR(Node* t, Node* x, int k) {
    Node* tk = t->next[k];
    if (tk == nullptr || x->key < tk->key) {
      if (k < x->sz) {
        x->next[k] = tk;
        t->next[k] = x;
      }
      if (k == 0) return;
      insertR(t, x, k - 1);
      return;
    }
    insertR(tk, x, k);
  }

  bool searchR(Node* t, int key, int k) const {
    if (t != head_ && key == t->key) return true;
    Node* x = t->next[k];
    if (x == nullptr || key < x->key) {
      if (k == 0) return false;
      return searchR(t, key, k - 1);
    }
    return searchR(x, key, k);
  }

  Node* head_;
  int lg_n_;  // current highest level in use
  std::mt19937 rng_;
};

}  // namespace ch13

#endif  // ALG_REF_CH13_SKIP_LIST_H_
