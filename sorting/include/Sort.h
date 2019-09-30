/*
 * Algorithms.h
 *
 *  Created on: 2011-11-30
 *      Author: morin
 */

#ifndef SORT_H_
#define SORT_H_

#include "SLList.h"

#include "utils.h"
#include "array.h"
#include "BinaryHeap.h"

namespace ods {

template<class T>
void merge(array<T> &a0, array<T> &a1, array<T> &a) {
	int i0 = 0, i1 = 0;
	for (int i = 0; i < a.length; i++) {
		if (i0 == a0.length) 		// all a0 are used
			a[i] = a1[i1++];
		else if (i1 == a1.length)  	// all a1 are used
			a[i] = a0[i0++];
		else if (compare(a0[i0], a1[i1]) < 0)
			a[i] = a0[i0++];
		else
			a[i] = a1[i1++];
	}
}

template<class T>
void mergeSort(array<T> &a) {
	if (a.length <= 1) return;
	array<T> a0(0);
	array<T>::copyOfRange(a0, a, 0, a.length/2);		// Left
	array<T> a1(0);
	array<T>::copyOfRange(a1, a, a.length/2, a.length); // Right
	mergeSort(a0);
	mergeSort(a1);
	merge(a0, a1, a);
}

template<class T>
void quickSort(array<T> &a) {
	quickSort(a, 0, a.length);
}

template<class T>
void quickSort(array<T> &a, int i, int n) {	// 3-Way Quick Sort, n is the length
	if (n <= 1) return;
	T x = a[i + rand()%n];			// Pick random pivot x
	int p = i-1, j = i, q = i+n;	// i=0 -> p=-1, j=0, q=n
	// a[i..p]<x,  a[p+1..q-1]??x, a[q..i+n-1]>x
	while (j < q) {
		int comp = compare(a[j], x);
		if (comp < 0) {       	// move to beginning of array
			a.swap(j++, ++p); 		// ++p is the starting of array
		} else if (comp > 0) { 	// move to end of array
			a.swap(j, --q);  		// --q is the end of array
									// j is not increased becaure swapped one can be larger than pivot
		} else {
			j++;              // keep in the middle
		}
	}
	// a[i..p]<x,  a[p+1..q-1]=x, a[q..i+n-1]>x 	// pivot a[6]
	//cout << i << " " << p << " " << q << " " << n << endl;
	//cout << i << " " << p-i+1 << endl;
	//cout << q << " " << n-(q-i) << endl;	// n is the length of (i,n] 
	quickSort(a, i, p-i+1); 	// if p=5, i=2, p=5 -> 2, 3, 4, 5  -> Length is 4 <- (5-2+1) = 4
	quickSort(a, q, n-(q-i));   // if q=7, i=2, n=9 -> 7, 8, 9, 10 -> Length is 4 <- 9-(7-2) = 4
								// Thus, (p-i+1) + (n-(q-i)) = 8 = n-1(pivot)
}

template<class T>
void heapSort(array<T> &a) {
	BinaryHeap<T>::sort(a);
}

// Only works for n integers (0, ..., n-1)
void countingSort(array<int> &a, int k) {	// k=n
	array<int> c(k, 0);
	for (int i = 0; i < a.length; i++)  	// Count each numbers frequency
		c[a[i]]++;
	for (int i = 1; i < k; i++)           	// Making each numbers (1...n-1) starting index 
		c[i] += c[i-1];
	array<int> b(a.length);
	for (int i = a.length-1; i >= 0; i--) 	// Directly fill from c not work if a has associated data
		b[--c[a[i]]] = a[i];
	a = b;
}

void radixSort(array<int> &a) {
	const int d = 8, w = 32;
	for (int p = 0; p < w/d; p++) {		// w/d passes
		array<int> c(1<<d, 0);			// the length c array
		// the next three for loops implement counting-sort
		array<int> b(a.length);
		for (int i = 0; i < a.length; i++)
			c[(a[i] >> d*p)&((1<<d)-1)]++;	// extract the integer whose binary rep. is given by the bits
		for (int i = 1; i < 1<<d; i++)
			c[i] += c[i-1];
		for (int i = a.length-1; i >= 0; i--)
			b[--c[(a[i] >> d*p)&((1<<d)-1)]] = a[i];
		a = b;
	}
}


} /* namespace ods */

#endif /* ALGORITHMS_H_ */
