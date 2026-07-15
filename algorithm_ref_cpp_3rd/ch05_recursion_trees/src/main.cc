// Chapter 5 driver: demonstrate the recursion and tree routines.
// No arguments required -- runs a built-in demo with labeled output.
//
//   ./ch05_recursion_trees_main

#include <chrono>
#include <iostream>
#include <vector>

#include "binary_tree.h"
#include "recursion.h"

using ch05::Count;
using ch05::Factorial;
using ch05::FibMemo;
using ch05::FibNaive;
using ch05::Gcd;
using ch05::Hanoi;
using ch05::Height;
using ch05::LevelOrder;
using ch05::MakeNode;
using ch05::MaxDivide;
using ch05::HanoiMoveCount;
using ch05::Node;
using ch05::NodePtr;
using ch05::PreorderRecursive;
using ch05::PreorderStack;

namespace {

void PrintVec(const std::vector<int>& v) {
  for (std::size_t i = 0; i < v.size(); ++i) {
    if (i) std::cout << ' ';
    std::cout << v[i];
  }
  std::cout << '\n';
}

// Build a small demo tree:
//
//            5
//          /   \
//         3     8
//        / \     \
//       1   4     9
//                /
//               7
NodePtr BuildDemoTree() {
  NodePtr root = MakeNode(5);
  root->l = MakeNode(3);
  root->r = MakeNode(8);
  root->l->l = MakeNode(1);
  root->l->r = MakeNode(4);
  root->r->r = MakeNode(9);
  root->r->r->l = MakeNode(7);
  return root;
}

}  // namespace

int main() {
  std::cout << "=== Chapter 5: Recursion and Trees ===\n\n";

  // --- Basic recursion --------------------------------------------------
  std::cout << "Factorial:\n";
  for (int n : {0, 1, 5, 10}) {
    std::cout << "  " << n << "! = " << Factorial(n) << '\n';
  }

  std::cout << "\nGreatest common divisor (Euclid):\n";
  std::cout << "  gcd(461952, 116298) = " << Gcd(461952, 116298) << '\n';
  std::cout << "  gcd(1071, 462)      = " << Gcd(1071, 462) << '\n';

  std::cout << "\nDivide-and-conquer max of array:\n";
  std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
  std::cout << "  data = ";
  PrintVec(data);
  std::cout << "  max  = " << MaxDivide(data) << '\n';

  // --- Towers of Hanoi --------------------------------------------------
  std::cout << "\nTowers of Hanoi:\n";
  for (int n : {1, 3, 5, 10}) {
    std::cout << "  N = " << n << " -> " << HanoiMoveCount(n) << " moves\n";
  }
  {
    std::cout << "  move sequence for N = 3 (from-peg -> to-peg):\n    ";
    std::vector<std::pair<int, int>> moves;
    Hanoi(3, 1, 3, 2, moves);
    for (std::size_t i = 0; i < moves.size(); ++i) {
      if (i) std::cout << ", ";
      std::cout << moves[i].first << "->" << moves[i].second;
    }
    std::cout << '\n';
  }

  // --- Fibonacci: naive vs. memoized ------------------------------------
  std::cout << "\nFibonacci (naive vs. memoized):\n";
  const int fib_n = 40;
  {
    auto t0 = std::chrono::steady_clock::now();
    long long naive = FibNaive(fib_n);
    auto t1 = std::chrono::steady_clock::now();
    long long memo = FibMemo(fib_n);
    auto t2 = std::chrono::steady_clock::now();
    auto us_naive =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    auto us_memo =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "  F(" << fib_n << ") naive = " << naive << "  (" << us_naive
              << " us)\n";
    std::cout << "  F(" << fib_n << ") memo  = " << memo << "  (" << us_memo
              << " us)\n";
  }

  // --- Binary tree ------------------------------------------------------
  std::cout << "\nBinary tree traversals:\n";
  NodePtr tree = BuildDemoTree();
  std::cout << "  node count = " << Count(tree.get()) << '\n';
  std::cout << "  height     = " << Height(tree.get()) << '\n';

  std::vector<int> pre;
  PreorderRecursive(tree.get(), pre);
  std::cout << "  preorder (recursive) = ";
  PrintVec(pre);
  std::cout << "  preorder (stack)     = ";
  PrintVec(PreorderStack(tree.get()));
  std::cout << "  level order (queue)  = ";
  PrintVec(LevelOrder(tree.get()));

  return 0;
}
