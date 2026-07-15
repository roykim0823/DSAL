#ifndef ALG_REF_CH04_QUEUE_H_
#define ALG_REF_CH04_QUEUE_H_

// Chapter 4: Abstract Data Types -- a generic FIFO QUEUE.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 4.
// The reference showed both a linked-list and a circular-array implementation
// (the latter requiring an explicit copy constructor, assignment and
// destructor).  Backing the queue with std::deque gives value semantics for
// free while keeping the same ADT interface:
//
//   empty() -- is the queue empty?
//   put(x)  -- append an item to the tail.
//   get()   -- remove and return the head item.

#include <deque>
#include <utility>

namespace ch04 {

template <class Item>
class Queue {
 public:
  Queue() = default;
  explicit Queue(int /*max_n*/) {}

  bool empty() const { return q_.empty(); }

  void put(Item item) { q_.push_back(std::move(item)); }

  Item get() {
    Item v = std::move(q_.front());
    q_.pop_front();
    return v;
  }

 private:
  std::deque<Item> q_;
};

}  // namespace ch04

#endif  // ALG_REF_CH04_QUEUE_H_
