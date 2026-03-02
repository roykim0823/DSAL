// Vector.h
// Created on: 2019-07-03
// Author: Hyunjin Kim

#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
#include <algorithm>

#include <stdlib.h>
#include <assert.h>
#include <memory>

namespace HKSTL {

// A simple array class that simulates Java's arrays implementation
// with a unique_pointer
template<typename T>
class Vector {
public:
  Vector(size_t length=1);
  Vector(size_t size, T value);
  virtual ~Vector() {}  // no need to deleate the memory

  void reserve(size_t n);
  bool empty() { return m_size==0; }
  size_t size() { return m_size; }
  size_t length() { return m_length; }
  void fill(T x);
	virtual void reverse();
  
  Vector<T>& operator=(const Vector<T> &vec);  // copy assignment
  Vector<T>& operator=(Vector<T> &&vec);  // move assignment

  T& operator[] (size_t i) {
    // assert( i >= 0 && i < m_size );
    assert( i >= 0 && i < m_length );
    return m_uniptr[i];
  }
  // operator overloading for the addrss addition 
	T* operator+(size_t i) { return &m_uniptr[i]; }
  

  // basic operations
  void push_back(const T& value);
  void pop_back();
  void insert(size_t i, const T& value);
  void erase(size_t i);  // remove i-th element
  void clear();  // remove all

protected:
  std::unique_ptr <T []> m_uniptr;
  std::size_t m_length;  // the length of allocated memory
  std::size_t m_size;  // the size of Vector
  void resize();
  void swap(size_t i, size_t j) {
    // std::swap(m_uniptr[i], m_uniptr[j]);
    T temp = m_uniptr[i];
    m_uniptr[i] = m_uniptr[j];
    m_uniptr[j] = temp;
  }
};

template<typename T>
Vector<T>::Vector(size_t length) {
  m_length = length;
  m_size = 0;
  m_uniptr = std::make_unique<T []>(m_length);
}

template<typename T>
Vector<T>::Vector(size_t size, T value) {
  m_length = size*2;
  m_size = size;
  m_uniptr = std::make_unique<T []>(m_length);
  for (size_t i=0; i<m_size; ++i) 
    m_uniptr[i] = value;
}

template <typename T>
void Vector<T>::reserve(size_t n) {
  if (m_length > n)
    return ;
  if (m_uniptr == nullptr) {  // empty vector
    m_length = n;
    m_size = 0;
    m_uniptr = std::make_unique<T []> (n);
  } else {
    std::unique_ptr<T []> temp(new T[n]);
    std::copy(&m_uniptr[0], &m_uniptr[m_size], &temp[0]);
    m_uniptr = std::move(temp);
  }
}

// copy assignment opeartor
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &vec) {
  std::unique_ptr <T[]> temp_uniptr(vec.size());
  std::copy(&(vec.m_uniptr[0]), &(vec.m_uniptr[vec.size()]), &temp_uniptr[0]);
  m_length = vec.m_length;
  m_size = vec.m_size;
  m_uniptr = std::move(temp_uniptr);
  return *this;
}

// move assignment opeartor
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &&vec) {
  std::swap(m_uniptr, vec.m_uniptr);
  std::swap(m_length, vec.m_length);
  std::swap(m_size, vec.m_size);
  return *this;
}

template<typename T>
void Vector<T>::reverse() {
  // reverse an Vector by swapping = n/2 complexity with in-place memory
	for (size_t i = 0; i < m_size/2; ++i) {
		swap(i, (m_size-1) - i);
	}
}
           
template<typename T>
void Vector<T>::fill(T value) {
	std::fill(m_uniptr, m_uniptr+m_size, value);
}

template <typename T>
void Vector<T>::push_back(const T& value) {
  if (m_size+1 >= m_length) resize();
  m_uniptr[m_size] = value;
  m_size++;
}

template <typename T>
void Vector<T>::pop_back() {
  m_size--;
  assert(m_size>=0);
  // resize (reduce the length) if the size <= 25% of the length
  if (m_size*4 <= m_length) resize();
}

template <typename T>
void Vector<T>::insert(size_t i, const T& value) {
  if (m_size+1 >= m_length) resize();
  std::copy_backward(&m_uniptr[i], &m_uniptr[m_size], &m_uniptr[m_size+1]);
  m_uniptr[i] = value;
  m_size++;
}

// remove i-th element
template <typename T>
void Vector<T>::erase(size_t i) {
  assert(i >=0 & i < m_size);
  std::copy(&m_uniptr[i+1], &m_uniptr[m_size], &m_uniptr[i]);
  m_size--;
  
  // resize (reduce the length) if the size <= 25% of the length
  if (m_size*4 <= m_length) resize();
}

// remove all
template <typename T>
void Vector<T>::clear() {
  m_length = 1;
  m_size = 0;
  std::unique_ptr<T []> tmp_ptr(new T[m_length]);
  m_uniptr = std::move(tmp_ptr);
}

template <typename T>
void Vector<T>::resize() {
  size_t new_length = m_size * 2;
  if (new_length == 0)
    new_length = 1;
  
  std::unique_ptr <T []> temp_ptr(new T[new_length]);
  std::copy(&m_uniptr[0], &m_uniptr[m_size], &temp_ptr[0]);

  m_length = new_length;
  m_uniptr = std::move(temp_ptr);
}

}  // namespace HKSTL
#endif  // VECTOR_H_
