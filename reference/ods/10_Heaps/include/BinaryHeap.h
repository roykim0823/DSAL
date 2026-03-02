/*
 * BinaryHeap.h
 *
 *  Created on: 2011-11-30
 *      Author: morin
 */

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <vector>
#include <algorithm>
#include <cstring>
#include "utils.h"

namespace ods {

template<class T>
class BinaryHeap {
protected:
	std::vector<T> a;
	int n;

	void resize();
	void bubbleUp(int i);
	void trickleDown(int i);
	void swap(int i, int j) {
		T t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	// class member function
	static int left(int i) 		{ return 2*i + 1; }
	static int right(int i) 	{ return 2*i + 2; }
	static int parent(int i) 	{ return (i-1)/2; }	// i >= 1
public:
	BinaryHeap(): n(0) {}
	BinaryHeap(std::vector<T>& b);
	virtual ~BinaryHeap() {}
	void add(T x);
	T findMin() { return a[0]; }
	T remove();
	int size() { return n; }
	void clear();
	static void sort(std::vector<T> &b);
};

template<class T>
BinaryHeap<T>::BinaryHeap(std::vector<T> &b) : a(b) {
	n = a.size();
	for (int i = n/2-1; i >= 0; i--) { 	// from last element of half covers all the elements
		trickleDown(i);
	}
}

template<class T>
void BinaryHeap<T>::resize() {
	a.resize(max(2*n,1));
}

template<class T>
void BinaryHeap<T>::sort(std::vector<T> &b) {
	BinaryHeap<T> h(b);
	while (h.n > 1) {
		//h.a.swap(--h.n, 0);
		h.swap(--h.n, 0); 	// swap the last elment to top
		h.trickleDown(0);
	}
	b = h.a;
	std::reverse(std::begin(b), std::end(b));	// b.reverse();
}

template<class T>
//bool BinaryHeap<T>::add(T x) {
void BinaryHeap<T>::add(T x) {
	if (n + 1 > (int)a.size()) resize();
	a[n++] = x;		// put the new element at the last
	bubbleUp(n-1);  // bubbleUp the new element : O(log n)
	//return true;
}

template<class T>
void BinaryHeap<T>::bubbleUp(int i) {
	int p = parent(i);
	while (i > 0 && compare(a[i], a[p]) < 0) { 	// compare node with its parent
		swap(i,p);	// swap if the parent is smaller
		i = p;
		p = parent(i);
	}
}

template<class T>
T BinaryHeap<T>::remove() {
	T x = a[0];  	// heap pops the root node
	a[0] = a[--n];  // the last node is moved to the root & decrease the size
	trickleDown(0); // O(log n)
	if (3*n < (int)a.size()) resize();
	return x;
}

template<class T>
void BinaryHeap<T>::trickleDown(int i) {
	do {
		int j = -1;
		int r = right(i);							// Choose the right child
		if (r < n && compare(a[r], a[i]) < 0) {    	// if a[r] < a[i]
			int l = left(i);
			if (compare(a[l], a[r]) < 0) {    		// Compare both children, then j=smaller one
				j = l;
			} else {
				j = r;
			}
		} else {                              		// Choose the left child
			int l = left(i);
			if (l < n && compare(a[l], a[i]) < 0) { // if a[l]<a[i]
				j = l;                              // j=l
			}
		}
		if (j >= 0)	swap(i, j); 	// swap
		i = j;                      // update i
	} while (i >= 0);
}


template<class T>
void BinaryHeap<T>::clear() {
	a.clear();
	n=0;
}

} /* namespace ods */
#endif /* BINARYHEAP_H_ */
