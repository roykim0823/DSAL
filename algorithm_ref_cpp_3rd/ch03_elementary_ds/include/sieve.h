#ifndef ALG_REF_CH03_SIEVE_H_
#define ALG_REF_CH03_SIEVE_H_

// Chapter 3: Elementary Data Structures -- the Sieve of Eratosthenes.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 3.
// The original marked a raw C array a[N]; here we return the primes in a
// std::vector<int> so callers own the result with no manual memory work.
//
// Complexity (primes below N):
//   time  O(N log log N)
//   space O(N)

#include <vector>

namespace ch03 {

// Returns every prime strictly less than n, in ascending order.
inline std::vector<int> PrimesBelow(int n) {
  std::vector<int> primes;
  if (n <= 2) return primes;

  // is_prime[i] stays true while i has no known smaller factor.
  std::vector<bool> is_prime(n, true);
  for (int i = 2; i < n; ++i) {
    if (!is_prime[i]) continue;
    // i is prime: strike out its multiples i*i, i*(i+1), ...
    for (long j = static_cast<long>(i) * i; j < n; j += i)
      is_prime[j] = false;
    primes.push_back(i);
  }
  return primes;
}

}  // namespace ch03

#endif  // ALG_REF_CH03_SIEVE_H_
