/*
 * basic sorting algorithms
 */

#ifndef SORT_H_
#define SORT_H_

#include "shuffle.h"
#include "utils.h"

#include <random>
#include <vector>
#include <utility>

namespace HKSTL {

enum class SortType { Select, Insert, Shell, Merge, Quick2WP, Quick,
                      CountSort, RadixSort, PigeonholeSort, BucketSort};

template <typename T>
void SelectionSort(std::vector<T>& vec) {
  for (int i=0; i<vec.size()-1; ++i) {
    int k = i;  // k is a index for min
    for (int j=i+1; j<vec.size(); ++j) {
      if (compare(vec[j], vec[k]) < 0)  // if vec[j] < vec[k]
        k = j;
    }
    std::swap(vec[i], vec[k]);
  }
}

template <typename T>
void InsertionSort(std::vector<T>& vec) {
  for (int i=1; i<vec.size(); ++i) {
    for (int j=i; j>0; --j) {
      if (compare(vec[j], vec[j-1]) < 0)  // if vec[j] < vec[j-1]
        std::swap(vec[j], vec[j-1]);
      else
        break;
    }
  }
}

template <typename T>
void ShellSort(std::vector<T>& vec) {
  int h = 1;
  while (h < vec.size()/3) h = 3*h + 1;  // 1, 4, 13, 40, 121, 364, ...

  while (h >= 1) {
    for (int i=h; i<vec.size(); ++i) {
      for (int j=i; j>= h && (compare(vec[j], vec[j-h]) < 0); j -= h)
        std::swap(vec[j], vec[j-h]);
    }
    h = h/3;
  }
}

// Merge Sort
template <typename T>
void merge(std::vector<T>& vec0, std::vector<T>& vec1, std::vector<T>& vec) {
  int i0 = 0, i1 = 0;
  for (int i=0; i<vec.size(); i++) {
    if (i0 == vec0.size())  // all vec0 are used
      vec[i] = vec1[i1++];
    else if (i1 == vec1.size())  // all vec1 are used
      vec[i] = vec0[i0++];
    else if (compare(vec0[i0], vec1[i1]) < 0)
      vec[i] = vec0[i0++];
    else
      vec[i] = vec1[i1++];
  }
}

template <typename T>
void MergeSort(std::vector<T>& vec) {
  if (vec.size() <= 1) return ;

  std::size_t half = vec.size()/2;
  std::vector<T> vec0, vec1;
  std::copy(vec.begin(), vec.begin()+half, std::back_inserter(vec0));  // Left
  std::copy(vec.begin()+half, vec.end(), std::back_inserter(vec1));  // Right
  MergeSort(vec0);
  MergeSort(vec1);
  merge(vec0, vec1, vec);
}

// QuickSort 2-way partition
template <typename T>
int partition(std::vector<T>& vec, int lo, int hi) {
  int i = lo, j = hi+1;
  while (true) {
    while (compare(vec[++i], vec[lo]) < 0)  // find item on left to swap
      if (i == hi) break;
    while (compare(vec[lo], vec[--j]) < 0)  // find item on right to swap
      if (j == lo) break;

    if (i >= j) break;  // check if pointers cross
    std::swap(vec[i], vec[j]);
  }
  std::swap(vec[lo], vec[j]);  // swap with partitioning item
  return j;  // return index of item now known to be in place
}

template <typename T>
void _quick_sort_2wp(std::vector<T>& vec, int lo, int hi) {
  if (hi <= lo) return;
  int j = partition(vec, lo, hi);
  _quick_sort_2wp(vec, lo, j-1);
  _quick_sort_2wp(vec, j+1, hi);
}

template <typename T>
void QuickSort2WP(std::vector<T>& vec) {
  Shuffle(vec);
  _quick_sort_2wp(vec, 0, vec.size()-1);
}

// QuckSort 3-wap partition to deal wtih duplicate keys
template <typename T>
void _quick_sort_3wp(std::vector<T>& vec, int lo, int hi) {
  if (hi <= lo) return;
  int lt = lo, gt = hi;
  int i=lo;
  T v = vec[lo];
  while (i <= gt) {
    int cmp = compare(vec[i], v);
    if (cmp < 0) std::swap(vec[lt++], vec[i++]);
    else if (cmp > 0) std::swap(vec[i], vec[gt--]);
    else i++;
  }
  _quick_sort_3wp(vec, lo, lt-1);
  _quick_sort_3wp(vec, gt+1, hi);
}


template <typename T>
void QuickSort(std::vector<T>& vec) {
  _quick_sort_3wp(vec, 0, vec.size()-1);
}

// Only works for n integers (0, ..., n-1)
void CountSort(std::vector<int> &a, int k) { // k=n
  std::vector<int> c(k, 0);
  for (int i = 0; i < a.size(); i++)  // Count each numbers frequency
    c[a[i]]++;
  for (int i = 1; i < k; i++)  // Making each numbers (1...n-1) starting index
    c[i] += c[i-1];

  std::vector<int> b(a.size());
  // Directly fill from c not work if a has associated data
  for (int i = a.size()-1; i >= 0; i--)
    b[--c[a[i]]] = a[i];
  a = b;
}

void RadixSort(std::vector<int> &a) {
  const int d = 8, w = 32;
  for (int p = 0; p < w/d; p++) {  // w/d passes
    std::vector<int> c(1<<d, 0);  // the length c array
    // the next three for loops implement counting-sort

    std::vector<int> b(a.size());
    // extract the integer whose binary rep. is given by the bits
    for (int i = 0; i < a.size(); i++)
      c[(a[i] >> d*p)&((1<<d)-1)]++;
    for (int i = 1; i < 1<<d; i++)
      c[i] += c[i-1];
    for (int i = a.size()-1; i >= 0; i--)
      b[--c[(a[i] >> d*p)&((1<<d)-1)]] = a[i];
    a = b;
  }
}

template <typename T>
void PigeonholeSort(std::vector<T>& vec) {
  // Find minimum and maximum values in the vector
  T min = vec[0], max = vec[0];
  for (int i=1; i<vec.size(); ++i) {
    if (vec[i] < min) 
      min = vec[i];
    if (vec[i] > max) 
      max = vec[i];
  }

  int range = max - min + 1;  // Find range

  // Create an array of vectors. Size of array range.
  // Each vector represents a hole that will contain matching elements.
  std::vector<T> holes[range];

  // Traverse through input vector and put every element in its respective hole
  for (int i=0; i < vec.size(); ++i)
    holes[vec[i]-min].push_back(vec[i]);

  // Traverse though all holes one by one. For every hole, take its elements 
  // and put in array.
  int idx = 0;  // index in sorted array
  for (int i=0; i<range; ++i) {
    for (auto iter = holes[i].begin(); iter != holes[i].end(); ++iter) {
      vec[idx++] = *iter;
    }
  }
}

// TODO: Use template for float or double type
// template <typename T>
void BucketSort(std::vector<float>& vec) 
{ 
    // 1) Create n empty buckets 
    std::vector<float> bucket[vec.size()]; 
     
    // 2) Put array elements in different buckets 
    for (int i=0; i<vec.size(); i++) {
       int idx = vec.size()*vec[i]; // Index in bucket 
       bucket[idx].push_back(vec[i]); 
    } 
  
    // 3) Sort individual buckets 
    for (int i=0; i<vec.size(); i++)
      InsertionSort(bucket[i]);
  
    // 4) Concatenate all buckets into arr[] 
    int index = 0; 
    for (int i = 0; i < vec.size(); i++) 
        for (int j = 0; j < bucket[i].size(); j++) 
          vec[index++] = bucket[i][j]; 
} 

template <typename T>
void Sort(std::vector<T>& vec, SortType sort_type, int n=0) {
  if (sort_type == SortType::Select) SelectionSort(vec);
  else if (sort_type == SortType::Insert) InsertionSort(vec);
  else if (sort_type == SortType::Shell) ShellSort(vec);
  else if (sort_type == SortType::Merge) MergeSort(vec);
  else if (sort_type == SortType::Quick2WP) QuickSort2WP(vec);
  else if (sort_type == SortType::Quick) QuickSort(vec);
  else if (sort_type == SortType::CountSort) CountSort(vec, n);
  else if (sort_type == SortType::RadixSort) RadixSort(vec);
  else if (sort_type == SortType::PigeonholeSort) PigeonholeSort(vec);
  // else if (sort_type == SortType::BucketSort) BucketSort(vec);
}

}  // namespace HKSTL
#endif   // SORT_H_
