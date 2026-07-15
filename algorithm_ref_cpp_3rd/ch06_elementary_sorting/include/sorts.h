#ifndef ALG_REF_CH06_SORTS_H_
#define ALG_REF_CH06_SORTS_H_

// Chapter 6: Elementary Sorting Methods.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 6.
// The original programs sorted raw C arrays via a template <class Item>;
// here each routine sorts the half-open-inclusive range a[l..r] of any
// container element type supporting operator<.  For convenience each sort
// also accepts a std::vector<Item> overload that covers the whole vector.
//
// Complexity (N = r - l + 1 items):
//   selection sort   O(N^2) comparisons, O(N)  exchanges
//   insertion sort   O(N^2) worst / O(N) nearly-sorted
//   bubble sort      O(N^2) comparisons and exchanges
//   shellsort        ~O(N^(3/2)) with the 1,4,13,40,... increments
//   distribution counting  O(N + M) for keys in [0, M)

#include <vector>

namespace ch06 {

// Swap two items.
template <class Item>
void exch(Item& a, Item& b) {
  Item t = a;
  a = b;
  b = t;
}

// Order two items so the smaller comes first.
template <class Item>
void compexch(Item& a, Item& b) {
  if (b < a) exch(a, b);
}

// Selection sort: repeatedly select the minimum of the remaining suffix.
template <class Item>
void selection(Item a[], int l, int r) {
  for (int i = l; i < r; i++) {
    int min = i;
    for (int j = i + 1; j <= r; j++)
      if (a[j] < a[min]) min = j;
    exch(a[i], a[min]);
  }
}

// Insertion sort: keep the prefix sorted, shifting to insert each new item.
template <class Item>
void insertion(Item a[], int l, int r) {
  for (int i = r; i > l; i--) compexch(a[i - 1], a[i]);  // sentinel: smallest to l
  for (int i = l + 2; i <= r; i++) {
    int j = i;
    Item v = a[i];
    while (v < a[j - 1]) {
      a[j] = a[j - 1];
      j--;
    }
    a[j] = v;
  }
}

// Bubble sort: bubble the smallest remaining item toward the front each pass.
template <class Item>
void bubble(Item a[], int l, int r) {
  for (int i = l; i < r; i++)
    for (int j = r; j > i; j--) compexch(a[j - 1], a[j]);
}

// Shellsort: h-sort with a decreasing sequence of increments (1, 4, 13, ...).
template <class Item>
void shellsort(Item a[], int l, int r) {
  int h;
  for (h = 1; h <= (r - l) / 9; h = 3 * h + 1) {
  }
  for (; h > 0; h /= 3)
    for (int i = l + h; i <= r; i++) {
      int j = i;
      Item v = a[i];
      while (j >= l + h && v < a[j - h]) {
        a[j] = a[j - h];
        j -= h;
      }
      a[j] = v;
    }
}

// Distribution counting: stable sort of small non-negative integer keys in
// [0, m).  Requires every key to satisfy 0 <= a[i] < m.
inline void distcount(int a[], int l, int r, int m) {
  std::vector<int> cnt(m + 1, 0);
  std::vector<int> b(r - l + 1);
  for (int i = l; i <= r; i++) cnt[a[i] + 1]++;
  for (int j = 1; j < m; j++) cnt[j] += cnt[j - 1];
  for (int i = l; i <= r; i++) b[cnt[a[i]]++] = a[i];
  for (int i = l; i <= r; i++) a[i] = b[i - l];
}

// Convenience overloads that sort an entire std::vector.
template <class Item>
void selection(std::vector<Item>& a) {
  if (!a.empty()) selection(a.data(), 0, static_cast<int>(a.size()) - 1);
}
template <class Item>
void insertion(std::vector<Item>& a) {
  if (!a.empty()) insertion(a.data(), 0, static_cast<int>(a.size()) - 1);
}
template <class Item>
void bubble(std::vector<Item>& a) {
  if (!a.empty()) bubble(a.data(), 0, static_cast<int>(a.size()) - 1);
}
template <class Item>
void shellsort(std::vector<Item>& a) {
  if (!a.empty()) shellsort(a.data(), 0, static_cast<int>(a.size()) - 1);
}
inline void distcount(std::vector<int>& a, int m) {
  if (!a.empty()) distcount(a.data(), 0, static_cast<int>(a.size()) - 1, m);
}

}  // namespace ch06

#endif  // ALG_REF_CH06_SORTS_H_
