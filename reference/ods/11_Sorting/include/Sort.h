/*
 * Algorithms.h
 *
 *  Created on: 2011-11-30
 *      Author: morin
 */

#ifndef SORT_H_
#define SORT_H_

#include <iostream>
#include <vector>
#include "utils.h"
#include "BinaryHeap.h"

namespace ods {

// Comparison-Based Sorting: merge-sort, quick-sort, and heap-sort

template<class T>
void merge(std::vector<T> &a0, std::vector<T> &a1, std::vector<T> &a) {
	int i0 = 0, i1 = 0;
	for (int i = 0; i < (int)a.size(); i++) {
		if (i0 == (int)a0.size()) 		// all a0 are used
			a[i] = a1[i1++];
		else if (i1 == (int)a1.size())  	// all a1 are used
			a[i] = a0[i0++];
		else if (compare(a0[i0], a1[i1]) < 0)
			a[i] = a0[i0++];
		else
			a[i] = a1[i1++];
	}
}

// divide and conquer recursively
template<class T>
void mergeSort(std::vector<T> &a) {
	if (a.size() <= 1) return;
	std::vector<T> a0(a.begin(), a.begin()+a.size()/2);			// copy the left half from a to a0
	std::vector<T> a1(a.begin()+a.size()/2, a.begin()+a.size());	// copy the right half from a to a1
	mergeSort(a0);
	mergeSort(a1);
	merge(a0, a1, a);
}


template<typename T>
void swap(std::vector<T> &v, int i, int j) {
	T tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

template<class T>
void print(std::vector<T> &a) {
	std::cout << "qsort = ";
	for(int i=0; i< (int)a.size(); i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}


/*
		< x if 0 <= i <= p
	a[i]= x if p <  i <  q
    	> x if q <= i <= n-1
*/
template<class T>
void quickSort(std::vector<T> &a, int i, int n) {	// 3-Way Quick Sort, n is the length
	if (n <= 1) return;	// ending condition

	T x = a[i + rand()%n];			// Pick random pivot x
	int p = i-1, j = i, q = i+n;	// i=0 -> p=-1, j=0, q=n
	// a[i..p]<x,  a[p+1..q-1]=x, a[q..i+n-1]>x
	// if(n<20) print(a); 	// n<20 -> print DEBUG info
	// if(n<20) cout << " x = " << x << " i= " << i << " n = " << n << endl;
	while (j < q) {
		int comp = compare(a[j], x);
		if (comp < 0) {       	// move to beginning of array
			swap<T>(a, j++, ++p); 		// ++p is the starting of array
		} else if (comp > 0) { 	// move to end of array
			swap<T>(a, j, --q);  		// --q is the end of array
									// j is not increased becaure swapped one can be larger than pivot
		} else {
			j++;              // keep in the middle
		}
	}
	// For Debugging
	// a[i..p]<x,  a[p+1..q-1]=x, a[q..i+n-1]>x 	// pivot a[6]
	// if(n<20) cout << i << " " << p << " " << q << " " << n << endl;
	// if(n<20) cout << i << " " << p-i+1 << endl;
	// if(n<20) cout << q << " " << n-(q-i) << endl;	// n is the length of (i,n]

	quickSort(a, i, p-i+1); 	// if p=5, i=2, p=5 -> 2, 3, 4, 5  -> Length is 4 <- (5-2+1) = 4
	quickSort(a, q, n-(q-i));   // if q=7, i=2, n=9 -> 7, 8, 9, 10 -> Length is 4 <- 9-(7-2) = 4
								// Thus, (p-i+1) + (n-(q-i)) = 8 = n-1(pivot)
}

template<class T>
void quickSort(std::vector<T> &a) {
	quickSort(a, 0, a.size());
}


template<class T>
void heapSort(std::vector<T> &a) {
	BinaryHeap<T>::sort(a);
}

// Not Comparison-Based Sorting: counting-sort, and radix-sort

// Only works for n integers (0, ..., n-1), O(n+k)
void countingSort(std::vector<int> &a, int k) {	// k=n
	std::vector<int> c(k, 0);
	for (int i = 0; i < (int)a.size(); i++)  	// Count each numbers frequency
		c[a[i]]++;
	for (int i = 1; i < k; i++)           	// Making each numbers (1...n-1) starting index
		c[i] += c[i-1];	// prefix sum
	std::vector<int> b(a.size());
	for (int i = a.size()-1; i >= 0; i--) 	// Directly fill from c not work if a has associated data
		b[--c[a[i]]] = a[i];
	a = b;
}

void radixSort(std::vector<int> &a) {	// O(cn), c=w/d
	const int d = 8, w = 32;
	for (int p = 0; p < w/d; p++) {		// w/d passes
		std::vector<int> c(1<<d, 0);			// the length c array
		// the next three for loops implement counting-sort
		std::vector<int> b(a.size());
		for (int i = 0; i < (int)a.size(); i++)
			c[(a[i] >> d*p) & ((1<<d)-1)]++;	// extract the integer whose binary rep. is given by the bits
		for (int i = 1; i < 1<<d; i++)
			c[i] += c[i-1];
		for (int i = a.size()-1; i >= 0; i--)
			b[--c[(a[i] >> d*p)&((1<<d)-1)]] = a[i];
		a = b;
	}
}


} /* namespace mySTL */

#endif /* ALGORITHMS_H_ */
