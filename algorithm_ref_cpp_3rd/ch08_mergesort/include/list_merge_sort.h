#ifndef ALG_REF_CH08_LIST_MERGE_SORT_H_
#define ALG_REF_CH08_LIST_MERGE_SORT_H_

// Chapter 8: Mergesort -- singly linked list mergesort.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 8.
// Mergesort is the natural sort for linked lists: it needs no random access
// and no auxiliary array -- links are simply rewired.  The list is split into
// halves with a slow/fast pointer, each half is sorted recursively, and the
// two sorted halves are merged by splicing nodes.
//
// Complexity (N nodes):
//   time     O(N log N)
//   space    O(log N) recursion stack; nodes are relinked in place
//   stability stable

namespace ch08 {

template <class Item>
struct ListNode {
  Item item;
  ListNode* next;
  explicit ListNode(const Item& v) : item(v), next(nullptr) {}
};

// Merge two sorted lists into one sorted list; returns the new head.
template <class Item>
ListNode<Item>* MergeLists(ListNode<Item>* a, ListNode<Item>* b) {
  ListNode<Item> dummy(Item{});
  ListNode<Item>* c = &dummy;
  while (a != nullptr && b != nullptr) {
    if (a->item < b->item) {
      c->next = a;
      c = a;
      a = a->next;
    } else {
      c->next = b;
      c = b;
      b = b->next;
    }
  }
  c->next = (a == nullptr) ? b : a;
  return dummy.next;
}

// Recursive list mergesort: split by slow/fast pointer, sort, merge.
template <class Item>
ListNode<Item>* MergeSortList(ListNode<Item>* head) {
  if (head == nullptr || head->next == nullptr) return head;

  // slow advances one node per step, fast two; when fast reaches the end,
  // slow sits at the tail of the first half.
  ListNode<Item>* slow = head;
  ListNode<Item>* fast = head->next;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  ListNode<Item>* second = slow->next;
  slow->next = nullptr;  // cut the list into two halves

  return MergeLists(MergeSortList(head), MergeSortList(second));
}

}  // namespace ch08

#endif  // ALG_REF_CH08_LIST_MERGE_SORT_H_
