#ifndef ALG_REF_CH09_PRIORITY_QUEUE_H_
#define ALG_REF_CH09_PRIORITY_QUEUE_H_

// Chapter 9: Priority Queues and Heapsort.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 9.
// The original programs operated on raw C arrays with a global exch(); here
// the heap lives in a std::vector and the priority queue is a templated class.
//
// A heap is an array arranged so that, for a node at index k, its children sit
// at 2k and 2k+1 and neither child exceeds the parent (a max-heap).  We use a
// 1-based layout (index 0 is unused) so the child/parent arithmetic matches
// the classic form.
//
// Building blocks (a[] is 1-based, valid entries a[1..N]):
//   fixUp(a, k)      -- swim a[k] up until the heap order is restored.
//   fixDown(a, k, N) -- sink a[k] down until the heap order is restored.
//
// Complexity (N elements):
//   fixUp / fixDown  O(log N)
//   PQ::insert       O(log N)
//   PQ::getmax       O(log N)
//   heapsort         O(N log N), in place, not stable
//   PQsort           O(N log N)

#include <cstddef>
#include <utility>
#include <vector>

namespace ch09 {

// Swim the item at index k toward the root while it is larger than its parent.
// a is 1-based; entry a[0] is ignored.
template <class Item>
void fixUp(std::vector<Item>& a, int k) {
  while (k > 1 && a[k / 2] < a[k]) {
    std::swap(a[k], a[k / 2]);
    k = k / 2;
  }
}

// Sink the item at index k toward the leaves while it is smaller than a child.
// Considers only the heap region a[1..N]; a is 1-based.
template <class Item>
void fixDown(std::vector<Item>& a, int k, int N) {
  while (2 * k <= N) {
    int j = 2 * k;
    if (j < N && a[j] < a[j + 1]) ++j;  // pick the larger child
    if (!(a[k] < a[j])) break;          // heap order already satisfied
    std::swap(a[k], a[j]);
    k = j;
  }
}

// Heap-based maximum-oriented priority queue.
template <class Item>
class PQ {
 public:
  // maxN is a size hint; the underlying storage still grows as needed.
  explicit PQ(int maxN = 0) : pq_(1), N_(0) { pq_.reserve(maxN + 1); }

  bool empty() const { return N_ == 0; }
  int size() const { return N_; }

  // Add an item and restore heap order.  O(log N).
  void insert(Item item) {
    pq_.push_back(std::move(item));
    ++N_;
    fixUp(pq_, N_);
  }

  // Remove and return the largest item.  O(log N).  Precondition: !empty().
  Item getmax() {
    std::swap(pq_[1], pq_[N_]);
    fixDown(pq_, 1, N_ - 1);
    Item max = std::move(pq_[N_]);
    pq_.pop_back();
    --N_;
    return max;
  }

 private:
  std::vector<Item> pq_;  // 1-based heap; pq_[0] unused
  int N_;                 // number of items currently stored
};

// Sort a[l..r] in place by pushing everything through a heap PQ.  O(N log N).
template <class Item>
void PQsort(std::vector<Item>& a, int l, int r) {
  PQ<Item> pq(r - l + 1);
  for (int k = l; k <= r; ++k) pq.insert(a[k]);
  for (int k = r; k >= l; --k) a[k] = pq.getmax();
}

// In-place heapsort of a[l..r]: bottom-up heap construction, then sortdown.
// O(N log N), not stable.
template <class Item>
void heapsort(std::vector<Item>& a, int l, int r) {
  int N = r - l + 1;
  // View the subrange as a 1-based heap by copying into scratch storage
  // (index 0 unused), sorting there, and writing back.  This keeps the clean
  // 1-based index arithmetic without mutating a[]'s indexing.
  std::vector<Item> pq(N + 1);
  for (int i = 0; i < N; ++i) pq[i + 1] = a[l + i];

  for (int k = N / 2; k >= 1; --k) fixDown(pq, k, N);
  while (N > 1) {
    std::swap(pq[1], pq[N]);
    fixDown(pq, 1, --N);
  }

  int total = r - l + 1;
  for (int i = 0; i < total; ++i) a[l + i] = pq[i + 1];
}

// Convenience overload: heapsort the whole vector.
template <class Item>
void heapsort(std::vector<Item>& a) {
  if (!a.empty()) heapsort(a, 0, static_cast<int>(a.size()) - 1);
}

}  // namespace ch09

#endif  // ALG_REF_CH09_PRIORITY_QUEUE_H_
