// Chapter 4 driver: exercise the abstract data types of Chapter 4 with a
// self-contained demo (no command-line arguments required).
//
//   ./ch04_abstract_data_types_main
//
// Three demos:
//   1. Stack   -- evaluate a postfix (reverse Polish) expression.
//   2. Complex -- print the N complex Nth roots of unity.
//   3. Poly    -- print the binomial coefficient rows of (x + 1)^n.

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "complex.h"
#include "poly.h"
#include "queue.h"
#include "stack.h"

using ch04::Complex;
using ch04::Poly;
using ch04::Stack;

namespace {

// Evaluate a whitespace-separated postfix expression of non-negative integers
// with the binary operators + and *.
int EvalPostfix(const std::string& expr) {
  Stack<int> save(static_cast<int>(expr.size()));
  std::istringstream in(expr);
  std::string tok;
  while (in >> tok) {
    if (tok == "+") {
      int b = save.pop(), a = save.pop();
      save.push(a + b);
    } else if (tok == "*") {
      int b = save.pop(), a = save.pop();
      save.push(a * b);
    } else {
      save.push(std::stoi(tok));
    }
  }
  return save.pop();
}

const double kPi = 3.14159265358979323846;

}  // namespace

int main() {
  // 1. Stack: postfix expression evaluation.
  const std::string expr = "5 9 8 + 4 6 * * 7 + *";
  std::cout << "Postfix evaluation\n";
  std::cout << "  \"" << expr << "\" = " << EvalPostfix(expr) << "\n\n";

  // 2. Complex: the N complex roots of unity.  Raising each to the Nth power
  //    should return (1, 0), confirming the roots.
  const int N = 8;
  std::cout << N << " complex roots of unity (root, then root^" << N << ")\n";
  for (int k = 0; k < N; ++k) {
    double theta = 2.0 * kPi * k / N;
    Complex t(std::cos(theta), std::sin(theta));
    Complex x = t;
    for (int j = 0; j < N - 1; ++j) x *= t;
    std::cout << "  " << k << ": (" << t << ")  ->  (" << x << ")\n";
  }
  std::cout << "\n";

  // 3. Poly: binomial coefficient rows from expanding (x + 1)^n.
  const int rows = 6;
  std::cout << "Binomial coefficients: rows of (x + 1)^n\n";
  Poly<int> x(1, 1), one(1, 0);  // x  and  1
  Poly<int> t = x + one;         // (x + 1)
  Poly<int> y = one;             // (x + 1)^0 = 1
  for (int i = 0; i <= rows; ++i) {
    std::cout << "  n=" << i << ": " << y << "\n";
    y = y * t;
  }

  return 0;
}
