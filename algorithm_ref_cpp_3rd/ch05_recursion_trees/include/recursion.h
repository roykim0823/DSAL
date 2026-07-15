#ifndef ALG_REF_CH05_RECURSION_H_
#define ALG_REF_CH05_RECURSION_H_

// Chapter 5: Recursion and Trees -- basic recursive algorithms.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 5.
// The originals used raw arrays and global state; here the routines take
// std::vector / value parameters and live in namespace ch05.
//
// Complexity summary (N = argument size):
//   Factorial   O(N)
//   Gcd         O(log(min(m, n)))  (Euclid)
//   MaxDivide   O(N)               (divide and conquer over an array)
//   Hanoi       O(2^N) moves       (moves(N) = 2^N - 1)
//   FibNaive    O(phi^N)           (exponential, no memoization)
//   FibMemo     O(N)               (top-down memoization)

#include <cstdint>
#include <utility>
#include <vector>

namespace ch05 {

// N! -- factorial.  Precondition: n >= 0.
inline long long Factorial(int n) {
  if (n <= 0) return 1;
  return static_cast<long long>(n) * Factorial(n - 1);
}

// Greatest common divisor via Euclid's algorithm.
inline int Gcd(int m, int n) {
  if (n == 0) return m;
  return Gcd(n, m % n);
}

// Divide-and-conquer maximum of a[l..r] (inclusive).  Precondition: l <= r.
inline int MaxDivide(const std::vector<int>& a, int l, int r) {
  if (l == r) return a[l];
  int m = (l + r) / 2;
  int u = MaxDivide(a, l, m);
  int v = MaxDivide(a, m + 1, r);
  return u > v ? u : v;
}

// Convenience overload: maximum of an entire (non-empty) vector.
inline int MaxDivide(const std::vector<int>& a) {
  return MaxDivide(a, 0, static_cast<int>(a.size()) - 1);
}

// Count the moves the Towers of Hanoi makes for N disks, appending each move
// (from-peg, to-peg, 1-based) to `moves`.  Total moves == 2^N - 1.
inline void Hanoi(int n, int from, int to, int via,
                  std::vector<std::pair<int, int>>& moves) {
  if (n == 0) return;
  Hanoi(n - 1, from, via, to, moves);
  moves.emplace_back(from, to);
  Hanoi(n - 1, via, to, from, moves);
}

// Number of moves the Towers of Hanoi requires for N disks (2^N - 1).
inline long long HanoiMoveCount(int n) {
  std::vector<std::pair<int, int>> moves;
  Hanoi(n, 1, 3, 2, moves);
  return static_cast<long long>(moves.size());
}

// Naive Fibonacci: F(0)=0, F(1)=1, F(i)=F(i-1)+F(i-2).  Exponential time.
inline long long FibNaive(int i) {
  if (i < 1) return 0;
  if (i == 1) return 1;
  return FibNaive(i - 1) + FibNaive(i - 2);
}

// Memoized Fibonacci: fills `known` (known[i] < 0 means "not yet computed").
inline long long FibMemo(int i, std::vector<long long>& known) {
  if (i < 1) return 0;
  if (i == 1) return 1;
  if (known[i] >= 0) return known[i];
  return known[i] = FibMemo(i - 1, known) + FibMemo(i - 2, known);
}

// Convenience overload: memoized Fibonacci with its own cache.
inline long long FibMemo(int i) {
  if (i < 1) return 0;
  std::vector<long long> known(i + 1, -1);
  return FibMemo(i, known);
}

}  // namespace ch05

#endif  // ALG_REF_CH05_RECURSION_H_
