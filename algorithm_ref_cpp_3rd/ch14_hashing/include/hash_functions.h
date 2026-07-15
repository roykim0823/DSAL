#ifndef ALG_REF_CH14_HASH_FUNCTIONS_H_
#define ALG_REF_CH14_HASH_FUNCTIONS_H_

// Chapter 14: Hashing -- hash functions for string and integer keys.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 14.
// The original programs hashed C strings by hand; here the same ideas are
// expressed with std::string and unsigned arithmetic (so the modulo can never
// go negative, unlike the signed-int version in the book).
//
//   HashString  -- Horner's method: h = (a*h + c) % M for each character.
//   HashInt     -- modular hash for integer keys: k % M.
//
// Complexity: O(len(key)) for strings, O(1) for ints.

#include <cstddef>
#include <string>

namespace ch14 {

// Horner's method with radix a = 127 over the characters of the key.
inline std::size_t HashString(const std::string& key, std::size_t m) {
  unsigned long h = 0;
  const unsigned long a = 127;
  for (char c : key)
    h = (a * h + static_cast<unsigned char>(c)) % m;
  return static_cast<std::size_t>(h);
}

// Simple modular hash for integer keys.
inline std::size_t HashInt(long key, std::size_t m) {
  unsigned long k = static_cast<unsigned long>(key);
  return static_cast<std::size_t>(k % m);
}

}  // namespace ch14

#endif  // ALG_REF_CH14_HASH_FUNCTIONS_H_
