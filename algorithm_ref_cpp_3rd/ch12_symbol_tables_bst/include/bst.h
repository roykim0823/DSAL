#ifndef ALG_REF_CH12_BST_H_
#define ALG_REF_CH12_BST_H_

// Chapter 12: Symbol Tables and BSTs -- a binary search tree symbol table.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 12.
// The original programs used raw node pointers and a hand-rolled Item class;
// here the table is templated on Key and Item and each node caches the size of
// its subtree so that select(k) / rank(key) run in tree height.
//
// Interface:
//   insert(key, item) -- add or overwrite an association
//   search(key)       -- return pointer to item, or nullptr if absent
//   contains(key)     -- membership test
//   show(os)          -- print keys/items in sorted (inorder) order
//   select(k)         -- the item with the k-th smallest key (0-based)
//   rank(key)         -- number of keys strictly smaller than key
//   remove(key)       -- delete an association (Hibbard deletion)
//   size()            -- number of associations
//
// Complexity (N keys), tree height h (h = O(log N) if balanced, O(N) worst):
//   insert / search / remove / select / rank : O(h)
//   show                                     : O(N)

#include <cstddef>
#include <ostream>

namespace ch12 {

template <class Key, class Item>
class BST {
 public:
  BST() = default;
  ~BST() { destroy(head_); }

  // Non-copyable for simplicity (raw owning pointers).
  BST(const BST&) = delete;
  BST& operator=(const BST&) = delete;

  int size() const { return count(head_); }

  // Insert (key, item); overwrites the item if key already present. O(h).
  void insert(const Key& key, const Item& item) { insertR(head_, key, item); }

  // Return a pointer to the item stored under key, or nullptr. O(h).
  const Item* search(const Key& key) const {
    node* h = head_;
    while (h != nullptr) {
      if (key < h->key)
        h = h->left;
      else if (h->key < key)
        h = h->right;
      else
        return &h->item;
    }
    return nullptr;
  }

  bool contains(const Key& key) const { return search(key) != nullptr; }

  // Print each (key, item) pair in ascending key order. O(N).
  void show(std::ostream& os) const { showR(head_, os); }

  // Item with the k-th smallest key (0-based); nullptr if k out of range. O(h).
  const Item* select(int k) const {
    node* h = head_;
    while (h != nullptr) {
      int t = count(h->left);
      if (t > k)
        h = h->left;
      else if (t < k) {
        h = h->right;
        k -= t + 1;
      } else {
        return &h->item;
      }
    }
    return nullptr;
  }

  // Number of keys strictly less than key. O(h).
  int rank(const Key& key) const {
    int r = 0;
    node* h = head_;
    while (h != nullptr) {
      if (key < h->key) {
        h = h->left;
      } else if (h->key < key) {
        r += count(h->left) + 1;
        h = h->right;
      } else {
        return r + count(h->left);
      }
    }
    return r;
  }

  // Remove the association for key, if present (Hibbard deletion). O(h).
  void remove(const Key& key) { removeR(head_, key); }

 private:
  struct node {
    Key key;
    Item item;
    node* left = nullptr;
    node* right = nullptr;
    int n = 1;  // size of the subtree rooted here
    node(const Key& k, const Item& x) : key(k), item(x) {}
  };

  static int count(node* h) { return h == nullptr ? 0 : h->n; }

  static void insertR(node*& h, const Key& key, const Item& item) {
    if (h == nullptr) {
      h = new node(key, item);
      return;
    }
    if (key < h->key)
      insertR(h->left, key, item);
    else if (h->key < key)
      insertR(h->right, key, item);
    else
      h->item = item;  // key already present: overwrite
    h->n = count(h->left) + count(h->right) + 1;
  }

  static void showR(node* h, std::ostream& os) {
    if (h == nullptr) return;
    showR(h->left, os);
    os << h->key << " " << h->item << "\n";
    showR(h->right, os);
  }

  static node* min(node* h) {
    while (h->left != nullptr) h = h->left;
    return h;
  }

  static void removeR(node*& h, const Key& key) {
    if (h == nullptr) return;
    if (key < h->key) {
      removeR(h->left, key);
    } else if (h->key < key) {
      removeR(h->right, key);
    } else {
      if (h->left == nullptr) {
        node* t = h;
        h = h->right;
        delete t;
        return;
      }
      if (h->right == nullptr) {
        node* t = h;
        h = h->left;
        delete t;
        return;
      }
      // Two children: replace with inorder successor (min of right subtree).
      node* succ = min(h->right);
      h->key = succ->key;
      h->item = succ->item;
      removeR(h->right, succ->key);
    }
    h->n = count(h->left) + count(h->right) + 1;
  }

  static void destroy(node* h) {
    if (h == nullptr) return;
    destroy(h->left);
    destroy(h->right);
    delete h;
  }

  node* head_ = nullptr;
};

}  // namespace ch12

#endif  // ALG_REF_CH12_BST_H_
