#ifndef ALG_REF_CH04_STACK_H_
#define ALG_REF_CH04_STACK_H_

// Chapter 4: Abstract Data Types -- a generic pushdown STACK.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 4.
// The original array-backed stack used raw pointers and a fixed maxN capacity;
// here the storage is a std::vector so the stack grows as needed.  The public
// interface mirrors the reference ADT:
//
//   empty() -- is the stack empty?
//   push(x) -- add an item to the top.
//   pop()   -- remove and return the top item.

#include <utility>
#include <vector>

namespace ch04 {

template <class Item>
class Stack {
 public:
  Stack() = default;
  explicit Stack(int max_n) { s_.reserve(max_n > 0 ? max_n : 0); }

  bool empty() const { return s_.empty(); }

  void push(Item item) { s_.push_back(std::move(item)); }

  Item pop() {
    Item v = std::move(s_.back());
    s_.pop_back();
    return v;
  }

 private:
  std::vector<Item> s_;
};

}  // namespace ch04

#endif  // ALG_REF_CH04_STACK_H_
