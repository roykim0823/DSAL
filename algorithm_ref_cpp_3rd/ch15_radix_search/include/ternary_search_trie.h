#ifndef ALG_REF_CH15_TERNARY_SEARCH_TRIE_H_
#define ALG_REF_CH15_TERNARY_SEARCH_TRIE_H_

// Chapter 15: Radix Search -- Ternary Search Trie (TST) for string keys.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 15.
// A TST is a hybrid of a trie and a BST: each node holds one character and
// three links -- left/right for characters smaller/larger than the node's
// character (like a BST) and a middle link that advances to the next character
// of the key (like a trie).  This keeps the space of an R-way trie low while
// preserving fast, prefix-based lookup.
//
// The digit accessor here is simply the d-th character of the key; the
// end-of-string sentinel ('\0') marks a stored value.
//
// Complexity (N keys, average length w, string length L on a hit):
//   insert  O(L + ln N)   -- one BST step per character
//   search  O(L + ln N)   -- misses often finish far sooner

#include <string>

namespace ch15 {

template <typename Value>
class TernarySearchTrie {
 public:
  TernarySearchTrie() = default;
  ~TernarySearchTrie() { destroy(head_); }

  TernarySearchTrie(const TernarySearchTrie&) = delete;
  TernarySearchTrie& operator=(const TernarySearchTrie&) = delete;

  // Insert key with associated val (overwrites value if key already present).
  void insert(const std::string& key, const Value& val) {
    head_ = insertR(head_, key, val, 0);
  }

  // Search for key; returns true and fills out with the value if found.
  bool search(const std::string& key, Value& out) const {
    const Node* h = searchR(head_, key, 0);
    if (h == nullptr || !h->has_value) return false;
    out = h->val;
    return true;
  }

  bool contains(const std::string& key) const {
    const Node* h = searchR(head_, key, 0);
    return h != nullptr && h->has_value;
  }

 private:
  struct Node {
    char c;
    bool has_value = false;
    Value val{};
    Node *l = nullptr, *m = nullptr, *r = nullptr;
    explicit Node(char ch) : c(ch) {}
  };

  // The digit accessor: d-th character of key, or '\0' past the end.
  static char digit(const std::string& key, int d) {
    return d < static_cast<int>(key.size()) ? key[d] : '\0';
  }

  Node* insertR(Node* h, const std::string& key, const Value& val, int d) {
    char c = digit(key, d);
    if (h == nullptr) h = new Node(c);
    if (c < h->c)
      h->l = insertR(h->l, key, val, d);
    else if (c > h->c)
      h->r = insertR(h->r, key, val, d);
    else if (c != '\0')
      h->m = insertR(h->m, key, val, d + 1);
    else {  // reached the end-of-string sentinel: store the value here
      h->has_value = true;
      h->val = val;
    }
    return h;
  }

  const Node* searchR(const Node* h, const std::string& key, int d) const {
    if (h == nullptr) return nullptr;
    char c = digit(key, d);
    if (c < h->c) return searchR(h->l, key, d);
    if (c > h->c) return searchR(h->r, key, d);
    if (c != '\0') return searchR(h->m, key, d + 1);
    return h;  // matched the terminating sentinel
  }

  static void destroy(Node* h) {
    if (h == nullptr) return;
    destroy(h->l);
    destroy(h->m);
    destroy(h->r);
    delete h;
  }

  Node* head_ = nullptr;
};

}  // namespace ch15

#endif  // ALG_REF_CH15_TERNARY_SEARCH_TRIE_H_
