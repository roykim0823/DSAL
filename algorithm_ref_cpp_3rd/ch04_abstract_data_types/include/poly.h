#ifndef ALG_REF_CH04_POLY_H_
#define ALG_REF_CH04_POLY_H_

// Chapter 4: Abstract Data Types -- a POLY polynomial template.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 4.
// A Poly<Number> represents c * x^N via a coefficient vector a[0..N] where
// a[i] is the coefficient of x^i.  Coefficients live in a std::vector so
// addition and multiplication size their result cleanly.  ADT interface:
//
//   Poly(c, N)  -- the single-term polynomial c * x^N.
//   eval(x)     -- Horner evaluation at x.
//   p + q, p * q -- polynomial arithmetic.

#include <ostream>
#include <vector>

namespace ch04 {

template <class Number>
class Poly {
 public:
  // The monomial c * x^N (degree N, so N+1 coefficients).
  Poly(Number c, int N) : a_(N + 1, Number(0)) { a_[N] = c; }

  double eval(double x) const {
    double t = 0.0;
    for (int i = static_cast<int>(a_.size()) - 1; i >= 0; --i)
      t = t * x + a_[i];
    return t;
  }

  const std::vector<Number>& coeffs() const { return a_; }

  friend Poly operator+(const Poly& p, const Poly& q) {
    Poly t(Number(0), (p.degree() > q.degree() ? p.degree() : q.degree()));
    for (std::size_t i = 0; i < p.a_.size(); ++i) t.a_[i] += p.a_[i];
    for (std::size_t j = 0; j < q.a_.size(); ++j) t.a_[j] += q.a_[j];
    return t;
  }

  friend Poly operator*(const Poly& p, const Poly& q) {
    Poly t(Number(0), p.degree() + q.degree());
    for (std::size_t i = 0; i < p.a_.size(); ++i)
      for (std::size_t j = 0; j < q.a_.size(); ++j)
        t.a_[i + j] += p.a_[i] * q.a_[j];
    return t;
  }

 private:
  int degree() const { return static_cast<int>(a_.size()) - 1; }

  std::vector<Number> a_;
};

template <class Number>
std::ostream& operator<<(std::ostream& out, const Poly<Number>& p) {
  const std::vector<Number>& a = p.coeffs();
  for (std::size_t i = 0; i < a.size(); ++i) {
    if (i) out << " ";
    out << a[i];
  }
  return out;
}

}  // namespace ch04

#endif  // ALG_REF_CH04_POLY_H_
