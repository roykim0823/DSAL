// Chapter 8 driver: demonstrate array mergesort (top-down and bottom-up) and
// linked-list mergesort.  No arguments required -- it runs a built-in demo.
//
//   ./ch08_mergesort_main

#include <iostream>
#include <string>
#include <vector>

#include "list_merge_sort.h"
#include "merge_sort.h"

namespace {

template <class Item>
void Print(const std::string& label, const std::vector<Item>& v) {
  std::cout << label;
  for (const Item& x : v) std::cout << ' ' << x;
  std::cout << '\n';
}

template <class Item>
bool IsSorted(const std::vector<Item>& v) {
  for (std::size_t i = 1; i < v.size(); ++i)
    if (v[i] < v[i - 1]) return false;
  return true;
}

// Build a linked list from the values; caller owns the returned nodes.
ch08::ListNode<int>* BuildList(const std::vector<int>& v) {
  ch08::ListNode<int>* head = nullptr;
  ch08::ListNode<int>* tail = nullptr;
  for (int x : v) {
    auto* node = new ch08::ListNode<int>(x);
    if (head == nullptr) {
      head = tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
  }
  return head;
}

void PrintList(const std::string& label, ch08::ListNode<int>* head) {
  std::cout << label;
  for (ch08::ListNode<int>* p = head; p != nullptr; p = p->next)
    std::cout << ' ' << p->item;
  std::cout << '\n';
}

void FreeList(ch08::ListNode<int>* head) {
  while (head != nullptr) {
    ch08::ListNode<int>* next = head->next;
    delete head;
    head = next;
  }
}

}  // namespace

int main() {
  const std::vector<int> sample = {5, 2, 8, 1, 9, 3, 7, 4, 6, 0, 5, 2};

  // Array mergesort -- top-down recursive.
  std::vector<int> td = sample;
  ch08::TopDownSort(td);
  Print("top-down  in :", sample);
  Print("top-down  out:", td);
  std::cout << "  sorted? " << (IsSorted(td) ? "yes" : "no") << "\n\n";

  // Array mergesort -- bottom-up iterative.
  std::vector<int> bu = sample;
  ch08::BottomUpSort(bu);
  Print("bottom-up out:", bu);
  std::cout << "  sorted? " << (IsSorted(bu) ? "yes" : "no") << "\n\n";

  // Two-way merge of two already-sorted arrays.
  const std::vector<int> a = {1, 4, 6, 9};
  const std::vector<int> b = {2, 3, 5, 8, 10};
  std::vector<int> merged(a.size() + b.size());
  ch08::MergeAB(merged.data(), a.data(), a.size(), b.data(), b.size());
  Print("mergeAB   a  :", a);
  Print("mergeAB   b  :", b);
  Print("mergeAB   out:", merged);
  std::cout << '\n';

  // Linked-list mergesort.
  ch08::ListNode<int>* list = BuildList(sample);
  PrintList("list      in :", list);
  list = ch08::MergeSortList(list);
  PrintList("list      out:", list);
  FreeList(list);

  return 0;
}
