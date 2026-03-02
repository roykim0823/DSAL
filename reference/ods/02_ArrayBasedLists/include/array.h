/*
 * array.h
 *
 *  Created on: 2011-11-24
 *      Author: morin
 */

#ifndef ARRAY_H_
#define ARRAY_H_
#include <iostream>
#include <algorithm>
#include <memory>

#include <stdlib.h>
#include <assert.h>

namespace ods {

/**
 * A simple array class that simulates Java's arrays implementation - kind of
 * TODO: Make a reference-counted version so that the = operator doesn't have
 * to destroy its right-hand side.
 */
template<typename T>
class array {
protected:
	//T *a;
	std::unique_ptr<T[]> a;
public:
	int length; 	// to keep track of its length, not good design (should be protected at least)

	array(int len=0);
	array(int len, T init);
	void fill(T x);
	virtual ~array();

	// Assign Operator Overloading
	array<T>& operator=(array<T> &b) {
		//if (a != nullptr) delete[] a;
		a = std::move(b.a);
		b.a = nullptr;
		length = b.length;
		return *this;
	}

	// Index Operator Overloading
	T& operator[](int i) {
		assert(i >= 0 && i < length);
		return a[i];
	}

	// Add operator Overaloading for the address addition
	T* operator+(int i) {
		return &a[i];
	}

	void swap(int i, int j) {
		T x = a[i];
		a[i] = a[j];
		a[j] = x;
	}

	// class member function: copy a[i:j] to a0
	static void copyOfRange(array<T> &a0, array<T> &a, int i, int j);

	virtual void reverse();
};

// Constructor with a length
template<typename T>
array<T>::array(int len) {
	length = len;
	//a = new T[length];
	a = std::unique_ptr<T[]>(new T[length]);
}

// Constructor with a length and initial value
template<typename T>
array<T>::array(int len, T init) {
	length = len;
	// a = new T[length];
	a = std::unique_ptr<T[]>(new T[length]);
	for (int i = 0; i < length; i++)
		a[i] = init;
}

// Default Destructor
template<typename T>
array<T>::~array() {
	//if (a != NULL) delete[] a;
}

template<typename T>
void array<T>::reverse() {	// reverse an array by swapping = n/2 complexity with in-place memory
	for (int i = 0; i < length/2; i++) {
		swap(i, length-i-1);
	}
}

template<typename T>
void array<T>::copyOfRange(array<T> &a0, array<T> &a, int i, int j) {
	array<T> b(j-i);
	std::copy(a.a, a.a+j-i, b.a);
	a0 = b;
}

template<typename T>
void array<T>::fill(T x) {
	std::fill(a.get(), a.get()+length, x);
}


} /* namespace ods */
#endif /* ARRAY_H_ */
