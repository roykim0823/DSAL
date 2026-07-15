#ifndef ALG_REF_CH04_COMPLEX_H_
#define ALG_REF_CH04_COMPLEX_H_

// Chapter 4: Abstract Data Types -- a first-class Complex number type.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 4.
// Faithful to the reference ADT: real/imaginary accessors plus operator*=
// for in-place multiplication.  operator* and stream output are provided so
// the type composes naturally in expressions.

#include <ostream>

namespace ch04 {

class Complex {
 public:
  Complex(double re, double im) : re_(re), im_(im) {}

  double Re() const { return re_; }
  double Im() const { return im_; }

  Complex& operator*=(const Complex& rhs) {
    double t = re_;
    re_ = re_ * rhs.re_ - im_ * rhs.im_;
    im_ = t * rhs.im_ + im_ * rhs.re_;
    return *this;
  }

 private:
  double re_, im_;
};

inline Complex operator*(Complex lhs, const Complex& rhs) {
  lhs *= rhs;
  return lhs;
}

inline std::ostream& operator<<(std::ostream& out, const Complex& c) {
  out << c.Re() << " " << c.Im();
  return out;
}

}  // namespace ch04

#endif  // ALG_REF_CH04_COMPLEX_H_
