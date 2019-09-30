/*
 * sl_list.h
 */

#ifndef SLLIST_H_
#define SLLIST_H_
#include <stdlib.h>

namespace HKSTL {

template<class T>  	
class SLList {	// Single-Linked List, a sequence of Nodes
protected:
	// 
	struct Node {
		T x;		// Data
		Node *next;	// Link
		Node(T x0): x(x0), next(nullptr) { } 
	};
	// For efficiency, SLList uses head and tail to keep track of the first and the last node
	Node *head;  // Head node
	Node *tail;  // Tail node: to implement add() function 
	size_t n;    // Size, the length of the sequence

public:
	SLList(): n(0), head(nullptr), tail(nullptr) {}
	virtual ~SLList() { clear(); }
	size_t size() { return n; 	}
	T front()     { return head->x; }
	T back()      { return tail->x; }
	void push_back(T x);
	void push_front(T x);
	void pop_front();
	void pop_back();	// inefficient in Single Linked List (requires linear traverse, O(n), idx-2)
	void clear();
  // subscript operator, O(n) -> idx-2 iterations
  T& operator[] (std::size_t idx);
  const T& operator[] (std::size_t idx) const;
};

// push_back() is inefficient if there is no tail node
template<typename T>
void SLList<T>::push_back(T x) {
	Node *u = new Node(x);
	if (n == 0) {
		head = u;		// head points to the new node if the list is empty
	} else {
		tail->next = u; // tail next points to the new node 
	}
	tail = u;			// move the tail to the new node
	n++;
}

template<typename T>
void SLList<T>::push_front(T x)	{
	Node *u = new Node(x);
	u->next = head;
	head = u;
	if (n == 0) {
		tail = u;		// tail points to the new node if the list is empty
	}
	n++;
}

template<typename T>
void SLList<T>::pop_front() {
	assert(n>0);
	Node *u = head;	// u points to the node that will be deleted	
	head = head->next;
	delete u;
	if (--n == 0) tail = nullptr;
}

template<typename T>
void SLList<T>::pop_back() {
	assert(n>0);
  if (n==1) {
    pop_front();
  } else { // n >= 2
	  Node *u = head;	// u points to the node that will be deleted
    while(u->next != tail) {
      u = u->next;
    }
    tail = u;
    delete tail->next;
    tail->next = nullptr;
    n--;
  }
}

template<typename T>
void SLList<T>::clear() {
	Node *u = head;
  	while (u != nullptr) {
   		Node *w = u;
   		u = u->next;
   		delete w;
   	}
}

template<typename T>
T& SLList<T>::operator[] (std::size_t idx) {
  Node *p = head;
  for(int i=0; i<idx; i++) 
    p = p->next;
  return p->x;
}

template<typename T>
const T& SLList<T>::operator[] (std::size_t idx) const {
  Node *p = head;
  for(int i=0; i<idx; i++) 
    p = p->next;
  return p->x;
}

} /* namespace HKSTL */
#endif /* SLLIST_H_ */
