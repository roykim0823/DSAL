/*
 * Knuth Shuffle
 */

#ifndef SHUFFLE_H_
#define SHUFFLE_H_

#include <random>
#include <vector>

namespace HKSTL {

template <typename T>
void Shuffle(std::vector<T>& vec) {
  std::default_random_engine generator;

  for (int i=0; i<vec.size(); ++i) {
    uniform_int_distribution<int> distribution(0, i);
    int r = distribution(generator);  // between 0 and i
    std::swap(vec[i], vec[r]);
  }
}

}  // namespace HKSTL

#endif   // SHUFFLE_H_
