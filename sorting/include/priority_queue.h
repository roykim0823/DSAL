#ifndef PRIORIT_QUEUE_H_
#define PRIORIT_QUEUE_H_

#include <iostream>
#include <vector>

namespace HKSTL {

// default Max Priority Queue with std::less<>, Min PQ with std::greater<>
template <typename T, typename U = std::less<>>
class PriorityQueue {
  std::vector<T> heap;// heap-ordered complete(full) binary tree
  int N;            // in heap[1..N] with heap[0] unused!
  bool compare(T a, T b, U u = U()) { return u(a, b); }

// Exchange key in child with key in parent
// Repeat until heap order restored
void swim(int k) {  // bubble up
  while (k>1 && compare(heap[k/2], heap[k])) {
    std::swap(heap[k/2], heap[k]);
    k = k/2;
  }
}

// Exchange key in parent with key in larger child in Max PQ
void sink(int k) {  // trickle down
  while(2*k <= N) {
    int j = 2*k;
    if(j<N && compare(heap[j], heap[j+1])) j++;
    if(!compare(heap[k], heap[j])) break;
    std::swap(heap[k], heap[j]);
    k = j;
  }
}

public:
  PriorityQueue(int max_N): N(0) { heap.resize(max_N + 1); }

  PriorityQueue(std::vector<T>& vec) {
    heap = vec;
    N = heap.size();
    // heap-ordered
    for(int k = N/2; k>=1; k--)
      sink(k, N);
  }

  bool isEmpty() { return (N==0); }
  int size() { return N; }

  void push(T v) {
    heap[++N] = v;
    swim(N);
    //heap.push_back(v);
    //swim(++N);
  }

  T top() { return heap[1]; }

  void pop() {
    std::swap(heap[1], heap[N--]);       // Exchange with last item.
    //heap.pop_back();    // Avoid litering
    //heap.resize(N);
    sink(1);  // Restore heap property
  }

};

template <typename T, typename U = std::less<>>
class Heap {
static bool compare(T a, T b, U u = U()) { return u(a, b); }

// Exchange key in child with key in parent
// Repeat until heap order restored
static void swim(std::vector<T>& heap, int k, int N) {  // bubble up
  while (k>1 && compare(heap[k/2], heap[k])) {
    std::swap(heap[k/2], heap[k]);
    k = k/2;
  }
}

// Exchange key in parent with key in larger child in Max PQ
static void sink(std::vector<T>& heap, int k, int N) {  // trickle down
  while(2*k <= N) {
    int j = 2*k;
    if(j<N && compare(heap[j], heap[j+1])) j++;
    if(!compare(heap[k], heap[j])) break;
    std::swap(heap[k], heap[j]);
    k = j;
  }
}

public:
  static void sort(std::vector<T>& vec) {
    int N = vec.size()-1;
    // make vec heap-ordered
    for (int k = N/2; k>=1; k--)
      sink(vec, k, N);
    // sorting
    while (N>1) {
      std::swap(vec[1], vec[N]);
      sink(vec, 1, --N);
    }
  }
};

}  // namespace HKSTL

#endif
