#ifndef ALG_REF_CH15_DIGITAL_SEARCH_TREE_H_
#define ALG_REF_CH15_DIGITAL_SEARCH_TREE_H_

// Chapter 15: Radix Search -- Digital Search Tree (DST) for integer keys.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 15.
// A DST is a binary tree in which the branch taken at depth d is decided by
// the d-th bit of the key (examined most-significant bit first) rather than by
// comparing whole keys as in a BST.  Every node stores a key/value pair; unlike
// a trie, keys live in internal nodes.
//
// The digit accessor is the heart of radix search: digit(v, d) returns bit d
// of key v counting from the most significant bit (bit 0 = MSB).
//
// Complexity (N keys of W bits):
//   insert  O(W)   -- one node visited per bit, at most W bits
//   search  O(W)   -- worst case proportional to key length, not to N

#include <cstdint>
#include <memory>
#include <utility>

namespace ch15 {

// Bit accessor: returns bit d of v, numbered from the most significant bit.
// Bits is the key width in bits (default 32 for uint32_t keys).
inline int digit(std::uint32_t v, int d, int bits = 32) {
  return static_cast<int>((v >> (bits - 1 - d)) & 1u);
}

template <typename Value>
class DigitalSearchTree {
 public:
  DigitalSearchTree() = default;

  // Insert key v with associated val (overwrites value if key already present).
  void insert(std::uint32_t v, const Value& val) { insertR(head_, v, val, 0); }

  // Search for key v; returns true and fills out with the value if found.
  bool search(std::uint32_t v, Value& out) const {
    const Node* h = searchR(head_.get(), v, 0);
    if (h == nullptr) return false;
    out = h->val;
    return true;
  }

  bool contains(std::uint32_t v) const {
    return searchR(head_.get(), v, 0) != nullptr;
  }

 private:
  struct Node {
    std::uint32_t key;
    Value val;
    std::unique_ptr<Node> l, r;
    Node(std::uint32_t k, const Value& v) : key(k), val(v) {}
  };

  void insertR(std::unique_ptr<Node>& h, std::uint32_t v, const Value& val,
               int d) {
    if (h == nullptr) {
      h.reset(new Node(v, val));
      return;
    }
    if (h->key == v) {
      h->val = val;
      return;
    }
    if (digit(v, d) == 0)
      insertR(h->l, v, val, d + 1);
    else
      insertR(h->r, v, val, d + 1);
  }

  const Node* searchR(const Node* h, std::uint32_t v, int d) const {
    if (h == nullptr) return nullptr;
    if (h->key == v) return h;
    if (digit(v, d) == 0)
      return searchR(h->l.get(), v, d + 1);
    else
      return searchR(h->r.get(), v, d + 1);
  }

  std::unique_ptr<Node> head_;
};

}  // namespace ch15

#endif  // ALG_REF_CH15_DIGITAL_SEARCH_TREE_H_
