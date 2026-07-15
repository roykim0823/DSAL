#ifndef ALG_REF_CH16_BTREE_ST_H_
#define ALG_REF_CH16_BTREE_ST_H_

// Chapter 16: External Searching -- a B-tree symbol table.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 16.
// The original used raw pointers, a global page capacity M and a nullItem
// sentinel; here the tree is a small class template parameterized on the
// key/value types and the branching factor M, and lookups report presence
// through a bool rather than a sentinel value.
//
// A B-tree is a multiway search tree in which every node (page) holds up to
// M-1 entries.  Internal pages store, for each child, the smallest key found
// in that subtree, so a search chooses the child whose separator range covers
// the target.  Overflowing pages split in half and push a copy of the split
// key up to the parent; when the root itself splits, a new root is created and
// the tree grows upward by one level.  This keeps the tree perfectly balanced,
// which matters when each page access is a slow external (disk) read.
//
// Complexity (N keys, branching factor M):
//   search  O(log_M N) page accesses, O(M * log_M N) key comparisons
//   insert  O(log_M N) page accesses
//   height  O(log_M N), and the tree is always balanced.

#include <algorithm>
#include <string>
#include <vector>

namespace ch16 {

// B-tree symbol table mapping Key -> Value.  M is the page branching factor:
// every page carries at most M-1 entries and splits at M.  M must be even and
// >= 4 so that both halves of a split remain non-empty.
template <class Key, class Value, int M = 4>
class BTreeST {
 public:
  BTreeST() : root_(new Node(true)), height_(0), size_(0) {}

  // Returns true and writes the value when v is present; false otherwise.
  bool search(const Key& v, Value& out) const {
    return SearchR(root_, v, out);
  }

  bool contains(const Key& v) const {
    Value ignored;
    return search(v, ignored);
  }

  // Insert or overwrite the entry for key v.
  void insert(const Key& v, const Value& item) {
    Node* overflow = InsertR(root_, v, item);
    if (overflow == nullptr) return;
    // Root split: build a new root over the two halves and grow upward.
    Node* t = new Node(false);
    t->entries.push_back(Entry(root_->entries.front().key, root_));
    t->entries.push_back(Entry(overflow->entries.front().key, overflow));
    root_ = t;
    ++height_;
  }

  int size() const { return size_; }
  int height() const { return height_; }  // number of internal levels

  // Level-order dump of the page structure for inspection.
  std::string LevelDump() const {
    std::string out;
    std::vector<Node*> level{root_};
    int depth = 0;
    while (!level.empty()) {
      std::vector<Node*> next;
      out += "  level " + std::to_string(depth) + ":";
      for (Node* n : level) {
        out += " [";
        for (size_t j = 0; j < n->entries.size(); ++j) {
          if (j) out += " ";
          out += KeyStr(n->entries[j].key);
          if (!n->leaf) next.push_back(n->entries[j].child);
        }
        out += "]";
      }
      out += "\n";
      level.swap(next);
      ++depth;
    }
    return out;
  }

 private:
  struct Node;

  // In a leaf, key/value hold real data.  In an internal page, key is the
  // smallest key in child's subtree and value is unused.
  struct Entry {
    Key key;
    Value value;
    Node* child;
    Entry() : child(nullptr) {}
    Entry(const Key& k, const Value& v) : key(k), value(v), child(nullptr) {}
    Entry(const Key& k, Node* c) : key(k), child(c) {}
  };

  struct Node {
    bool leaf;
    std::vector<Entry> entries;  // kept sorted by key
    explicit Node(bool is_leaf) : leaf(is_leaf) { entries.reserve(M); }
  };

  static bool SearchR(Node* h, const Key& v, Value& out) {
    if (h->leaf) {
      for (const Entry& e : h->entries)
        if (e.key == v) {
          out = e.value;
          return true;
        }
      return false;
    }
    // Descend into the child whose separator range covers v.
    for (size_t j = 0; j < h->entries.size(); ++j) {
      if (j + 1 == h->entries.size() || v < h->entries[j + 1].key)
        return SearchR(h->entries[j].child, v, out);
    }
    return false;
  }

  // Inserts (v, item) beneath h.  Returns the new right-half page if h split,
  // otherwise nullptr.  Updates size_ on genuine insertions.
  Node* InsertR(Node* h, const Key& v, const Value& item) {
    if (h->leaf) {
      size_t j = 0;
      while (j < h->entries.size() && h->entries[j].key < v) ++j;
      if (j < h->entries.size() && h->entries[j].key == v) {
        h->entries[j].value = item;  // overwrite, no growth
        return nullptr;
      }
      h->entries.insert(h->entries.begin() + j, Entry(v, item));
      ++size_;
    } else {
      size_t j = 0;
      for (; j < h->entries.size(); ++j)
        if (j + 1 == h->entries.size() || v < h->entries[j + 1].key) break;
      Node* overflow = InsertR(h->entries[j].child, v, item);
      if (overflow == nullptr) return nullptr;
      // Child split: insert a separator for the new right half after j.
      h->entries.insert(h->entries.begin() + j + 1,
                        Entry(overflow->entries.front().key, overflow));
    }
    if (static_cast<int>(h->entries.size()) < M) return nullptr;
    return Split(h);
  }

  // Moves the upper half of h into a fresh page and returns it.
  static Node* Split(Node* h) {
    Node* t = new Node(h->leaf);
    const size_t half = h->entries.size() / 2;
    t->entries.assign(h->entries.begin() + half, h->entries.end());
    h->entries.erase(h->entries.begin() + half, h->entries.end());
    return t;
  }

  static std::string KeyStr(const Key& k) { return ToStr(k); }
  static std::string ToStr(const std::string& s) { return s; }
  template <class T>
  static std::string ToStr(const T& k) { return std::to_string(k); }

  Node* root_;
  int height_;
  int size_;
};

}  // namespace ch16

#endif  // ALG_REF_CH16_BTREE_ST_H_
