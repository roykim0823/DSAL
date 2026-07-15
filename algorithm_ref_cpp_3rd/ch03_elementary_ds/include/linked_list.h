#ifndef ALG_REF_CH03_LINKED_LIST_H_
#define ALG_REF_CH03_LINKED_LIST_H_

// Chapter 3: Elementary Data Structures -- singly-linked list applications.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 3.
// Kept a hand-rolled node to stay faithful to the original `struct node`.
// Josephus owns the ring it builds and frees every node before returning;
// Reverse only rewires existing pointers, so the caller owns those nodes.
//
// Contents:
//   Josephus(n, m)  -- survivor of the Josephus elimination, O(n*m) time.
//   Reverse(head)   -- in-place reversal of a singly-linked list, O(n) time.

namespace ch03 {

// Faithful singly-linked node: an item plus a raw `next` pointer.
struct Node {
  int item;
  Node* next;
  Node(int x, Node* t) : item(x), next(t) {}
};

// Josephus problem: n people numbered 1..n stand in a circle and every m-th
// person is eliminated until one remains.  Returns the survivor's number.
//
// Builds a circular list (as in Sedgewick), advances m-1 links, then splices
// out the following node.  Frees every node before returning.
inline int Josephus(int n, int m) {
  if (n <= 0 || m <= 0) return -1;

  // Build the ring 1 -> 2 -> ... -> n -> (back to 1).
  Node* head = new Node(1, nullptr);
  head->next = head;
  Node* x = head;
  for (int i = 2; i <= n; ++i)
    x = (x->next = new Node(i, head));

  // Eliminate until a single node points to itself.
  while (x != x->next) {
    for (int i = 1; i < m; ++i) x = x->next;
    Node* doomed = x->next;
    x->next = doomed->next;
    delete doomed;
  }

  int survivor = x->item;
  delete x;
  return survivor;
}

// In-place reversal of a null-terminated singly-linked list.  Rewires the
// existing `next` pointers (no allocation) and returns the new head.
inline Node* Reverse(Node* head) {
  Node* reversed = nullptr;
  while (head != nullptr) {
    Node* rest = head->next;
    head->next = reversed;
    reversed = head;
    head = rest;
  }
  return reversed;
}

}  // namespace ch03

#endif  // ALG_REF_CH03_LINKED_LIST_H_
