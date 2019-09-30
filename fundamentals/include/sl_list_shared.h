/*
 * sl_list_shared.h
 */

#ifndef SLLIST_SHARED_H_
#define SLLIST_SHARED_H_
#include <memory>	// shared_ptr

namespace HKSTL {

template<class T>  	
// It is hard to make place holders (head and tail) unique_pointer 
class SLList_SHARED {	// Single-Linked List, a sequence of Nodes
protected:
	// 
	struct Node {
		T x;		// Data
		std::shared_ptr<Node> next;	// Link
		Node(T x0) { 	// Constructor
			x = x0; 	// rev from: x=0
			next = nullptr;
		}
		~Node() {
			//cout << "delete " << x << endl;
		}
	};
	// For efficiency, SLList_SHARED uses head and tail to keep track of the first and the last node
	std::shared_ptr<Node> head; 	// Head node
	std::shared_ptr<Node> tail;   	// Tail node: to implement push_back() function 
	size_t n;         	// Size, the length of the sequence

public:
	SLList_SHARED() {
		n = 0;
		head = tail = nullptr;
	}

	virtual ~SLList_SHARED() { clear(); }

	size_t size() 	{ return n; 	}
	T front() 	{ return head->x; }
	T back() 	{ return tail->x; }
	void push_back(T x);
	void push_front(T x);
	void pop_front();
	void pop_back();	// inefficient in Single Linked List (requires linear traverse)
	void clear();
  // subscript operator, O(n)
  T& operator[] (std::size_t idx);
  const T& operator[] (std::size_t idx) const;
};

// push_back() is inefficient if there is no tail node
template<typename T>
void SLList_SHARED<T>::push_back(T x)	{
	// std::shared_ptr<Node> u(new Node(x));
	std::shared_ptr<Node> u = std::make_shared<Node>(x);
	if (n == 0) {
		head = u;		// head points to the new node if the list is empty
	} else {
		tail->next = u; // tail next points to the new node 
	}
	tail = u;			// move the tail to the new node
	n++;
}

template<typename T>
void SLList_SHARED<T>::push_front(T x) {
	// Node *u = new Node(x);
	// std::shared_ptr<Node> u(new Node(x));
	std::shared_ptr<Node> u = std::make_shared<Node>(x);
	u->next = head;
	head = u;
	if (n == 0) {
		tail = u;		// tail points to the new node if the list is empty
	}
	n++;
}

template<typename T>
void SLList_SHARED<T>::pop_front() {
	assert(n>0);
	//Node *u = head;	// u points to the node that will be deleted	
	head = head->next;
	//delete u;
	if (--n == 0) tail = nullptr;
}

template<typename T>
void SLList_SHARED<T>::pop_back() {
  assert(n>0);
  if (n==1) {
    pop_front();
  } else {  // n >= 2
	  auto u = head;
    while (u->next != tail) {
      u = u->next;
    }
    tail = u;
    tail->next = nullptr;
    n--;
  }
}

template<typename T>
void SLList_SHARED<T>::clear() {
	std::shared_ptr<Node> u = head;
  while (u != NULL) {
   	//Node *w = u;
   	u = u->next;
   	//delete w;
  }
}

template <typename T>
T& SLList_SHARED<T>::operator[] (std::size_t idx) {
  auto p = head;
  for(int i=0; i<idx; i++) 
    p = p->next;
  return p->x;
}

template <typename T>
const T& SLList_SHARED<T>::operator[] (std::size_t idx) const {
  auto p = head;
  for(int i=0; i<idx; i++) 
    p = p->next;
  return p->x;
}
}  // namespace HKSTL 
#endif  // SLLIST_SHARED_H_
