#ifndef ALG_REF_CH13_RED_BLACK_BST_H_
#define ALG_REF_CH13_RED_BLACK_BST_H_

// Chapter 13: Balanced Trees -- red-black BST symbol table (int keys).
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 13
// (the RBinsert snippet with top-down color flips and rotations).  The
// original used raw node pointers and an Item/Key abstraction; here keys are
// plain ints and memory is owned by the tree (freed in the destructor).
//
// A red-black BST is a BST whose nodes carry a color (red/black) such that no
// path from the root to a null link has two consecutive red links and every
// such path has the same number of black links.  This keeps the tree
// height-balanced, giving logarithmic search and insert.
//
// Interface:
//   insert(key) -- add a key (duplicates go to the right subtree).
//   contains(key) -- is key present?
//   inorder() -- keys in sorted order.
//
// Complexity (N keys):
//   search  O(log N)
//   insert  O(log N)

#include <vector>

namespace ch13 {

class RedBlackBST {
 public:
  RedBlackBST() = default;
  ~RedBlackBST() { destroy(head_); }

  RedBlackBST(const RedBlackBST&) = delete;
  RedBlackBST& operator=(const RedBlackBST&) = delete;

  void insert(int key) {
    RBinsert(head_, key, 0);
    head_->red = false;  // the root is always black
  }

  bool contains(int key) const {
    for (Node* x = head_; x != nullptr;) {
      if (key == x->key) return true;
      x = (key < x->key) ? x->l : x->r;
    }
    return false;
  }

  // Keys in ascending order (in-order traversal).
  std::vector<int> inorder() const {
    std::vector<int> out;
    inorderR(head_, out);
    return out;
  }

 private:
  struct Node {
    int key;
    bool red;  // color of the link pointing to this node
    Node* l;
    Node* r;
    explicit Node(int k) : key(k), red(true), l(nullptr), r(nullptr) {}
  };

  static bool red(Node* x) { return x != nullptr && x->red; }

  // Right rotation: h's left child becomes the new subtree root.
  static void rotR(Node*& h) {
    Node* x = h->l;
    h->l = x->r;
    x->r = h;
    h = x;
  }

  // Left rotation: h's right child becomes the new subtree root.
  static void rotL(Node*& h) {
    Node* x = h->r;
    h->r = x->l;
    x->l = h;
    h = x;
  }

  void RBinsert(Node*& h, int key, int sw) {
    if (h == nullptr) {
      h = new Node(key);
      return;
    }
    if (red(h->l) && red(h->r)) {  // split a 4-node on the way down
      h->red = true;
      h->l->red = false;
      h->r->red = false;
    }
    if (key < h->key) {
      RBinsert(h->l, key, 0);
      if (red(h) && red(h->l) && sw) rotR(h);
      if (red(h->l) && red(h->l->l)) {
        rotR(h);
        h->red = false;
        h->r->red = true;
      }
    } else {
      RBinsert(h->r, key, 1);
      if (red(h) && red(h->r) && !sw) rotL(h);
      if (red(h->r) && red(h->r->r)) {
        rotL(h);
        h->red = false;
        h->l->red = true;
      }
    }
  }

  static void inorderR(Node* h, std::vector<int>& out) {
    if (h == nullptr) return;
    inorderR(h->l, out);
    out.push_back(h->key);
    inorderR(h->r, out);
  }

  static void destroy(Node* h) {
    if (h == nullptr) return;
    destroy(h->l);
    destroy(h->r);
    delete h;
  }

  Node* head_ = nullptr;
};

}  // namespace ch13

#endif  // ALG_REF_CH13_RED_BLACK_BST_H_
