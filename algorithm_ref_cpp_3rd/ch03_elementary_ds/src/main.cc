// Chapter 3 driver: demonstrate three elementary data-structure algorithms.
//
//   ./ch03_elementary_ds_main   # runs the built-in demo (no arguments)
//
// Output sections:
//   1. Sieve of Eratosthenes  -- primes below a sample bound.
//   2. Josephus problem       -- survivor for a sample (N, M).
//   3. Linked-list reversal   -- a list printed before and after reversal.

#include <iostream>
#include <vector>

#include "linked_list.h"
#include "sieve.h"

using ch03::Node;

namespace {

// Prints "1 -> 2 -> 3 -> null" for a null-terminated list.
void PrintList(const Node* head) {
  for (const Node* p = head; p != nullptr; p = p->next)
    std::cout << p->item << " -> ";
  std::cout << "null\n";
}

// Builds 1 -> 2 -> ... -> n as a plain (non-circular) list.
Node* BuildRange(int n) {
  Node* head = nullptr;
  for (int i = n; i >= 1; --i) head = new Node(i, head);
  return head;
}

void FreeList(Node* head) {
  while (head != nullptr) {
    Node* next = head->next;
    delete head;
    head = next;
  }
}

}  // namespace

int main() {
  // 1. Sieve of Eratosthenes.
  const int kSieveBound = 100;
  std::cout << "Primes below " << kSieveBound << ":\n ";
  for (int p : ch03::PrimesBelow(kSieveBound)) std::cout << ' ' << p;
  std::cout << "\n\n";

  // 2. Josephus problem.
  const int kN = 9, kM = 5;
  std::cout << "Josephus problem (N = " << kN << ", M = " << kM << "):\n";
  std::cout << "  survivor is person #" << ch03::Josephus(kN, kM) << "\n\n";

  // 3. In-place linked-list reversal.
  std::cout << "Linked-list reversal:\n";
  Node* list = BuildRange(8);
  std::cout << "  before: ";
  PrintList(list);
  list = ch03::Reverse(list);
  std::cout << "  after:  ";
  PrintList(list);
  FreeList(list);

  return 0;
}
