/*
 * ArrayQueue.h
 *
 *  Created on: 2011-11-23
 *      Author: morin
 */

#ifndef ARRAYQUEUE_H_
#define ARRAYQUEUE_H_
#include "array.h"

namespace ods {

template<class T>
class ArrayQueue {	// queue by circular array using modulo operation
protected:
	array<T> a;  	// Circular array
	int j;          // Starting index
	int n;          // The length of array
	void resize();
public:
	ArrayQueue();
	virtual ~ArrayQueue();
	virtual bool add(T x);
	virtual T remove();
	int size();
};

template<class T>
ArrayQueue<T>::ArrayQueue() : a(1) {	// a(1), a's size is 1
	n = 0;
	j = 0;
}

template<class T>
ArrayQueue<T>::~ArrayQueue() {
	delete a;
}

template<class T>
void ArrayQueue<T>::resize() {
	array<T> b(max(1, 2*n));
	for (int k = 0; k < n; k++)
		b[k] = a[(j+k)%a.length];	// Copy by modular arithmetic
	a = b;	// array<T> assignment
    j = 0;
}

template<class T>
bool ArrayQueue<T>::add(T x) {   	
	 if (n + 1 > a.length) resize();
	 a[(j+n) % a.length] = x;   	// Add an item at the end
	 n++;
	 return true;
 }

template<class T>
T ArrayQueue<T>::remove() {
	T x = a[j];
	j = (j + 1) % a.length;			// remove an item by increasing the staring index
	n--;
	if (a.length >= 3*n) resize();
	return x;
}

template<class T>
int ArrayQueue<T>::size() {
	return n;
}

} /* namespace ods */
#endif /* ARRAYQUEUE_H_ */
