## header files
- array.h: Array + ArrayStack + FastArrayStack in ODS
- vector.h: array.h implementation with std::shared_ptr
- deque.h: double-ended queue with Vector using a circular array with modular op
- queue.h: queue with Vector using a circular array with modular op
- sl_list.h: single linked list with push and pop both sides
- sl_list_shared.h: single linked list with std::shared_ptr
- dl_list.h: double linked list with push and pop both sides
- dl_list_shared.h: double linked list with std::shared_ptr
three\_sum.h : find three number to a sum

## Resizing-array efficient solutions
When array is full, double size of array.
When array is 25% full, halve size of array.
-> Amortized Cost: 3

## Single Linked List vs. Double Linked List
- front() and back(): O(1), SLL with a tail pointer
- push_front(), push_back(): O(1)
- pop_front(): O(1)
- pop_back(): O(n) in SLL, O(1) in DLL
- operator[]: O(n) in SLL and DLL (DLL takes n/2)

## Stack and Queue implementation: linked-list vs. resizing array
- Linked-list
  1. Every operation takes constant time in the worst case.
  2. Use extra time and space to deal with the links
- Resizing array
  1. Every operation takes constant amorized time.
    - Latency of operations can be varied
  2. Less wasted space.

## QuickFind vs. QuickUnion
- Quick-find defect
  1. Union too expensive, O(n)
  2. Trees are flat, but too expensive to keep them flat.
- QuickUnion defect
  1. Trees can get tall.
  2. Find too expensive, could be O(n)

## TODO
trimeed test (reduce #files)
