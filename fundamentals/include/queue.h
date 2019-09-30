// Queue.h
// Created on: 2019-07-20
// Author: Hyunjin Kim

#ifndef QUEUE_H_
#define QUEUE_H_
#include "utils.h"
#include "vector.h"

namespace HKSTL {

template <typename T>
class Queue {	 // queue by circular array using modulo operation
protected:
	Vector<T> m_vec;  // Circular array
	size_t m_beg;     // Starting index
	size_t m_size;    // The size of m_vec
	void resize();
public:
	Queue();
	virtual ~Queue()  {}
	virtual void push(T x);  // add element to the end
	virtual void pop();  // remove element from the start
	int size();

  T front() { return m_vec[m_beg]; }
  T back() { return m_vec[(m_beg+(m_size-1)) % m_vec.length()]; }
};

template <typename T>
Queue<T>::Queue() : m_vec(8) {
	m_beg = 0;
  m_size = 0;
}

template <typename T>
void Queue<T>::resize() {
	Vector<T> tmp(max((size_t)1, 2 * m_size));
	for (int k = 0; k < m_size; k++)
		tmp[k] = m_vec[(m_beg+k) % m_vec.length()];	 // Copy by modular arithmetic
	m_vec = std::move(tmp);	 
  m_beg = 0;
}

template <typename T>
void Queue<T>::push(T x) {   	
	 if (m_size + 1 > m_vec.length()) resize();
	 m_vec[(m_beg+m_size) % m_vec.length()] = x;   	// Add an item at the end
	 m_size++;
}

template <typename T>
void Queue<T>::pop() {
	m_beg = (m_beg + 1) % m_vec.length();  // remove an item by increasing the staring index
	m_size--;
	if (m_vec.length() >= m_size * 4) resize();
}

template <typename T>
int Queue<T>::size() {
	return m_size;
}

}  // namespace HKSTL 
#endif  // QUEUE_H_ 
