/*
 * dl_list.h
 *
 */

#ifndef DLLIST_H_
#define DLLIST_H_

namespace HKSTL {

template<class T>
class DLList {
protected:
	class Node {
	public:
		T x;
		Node *prev, *next;	// two pointers
	};
	Node dummy;	// acts as a placeholder (no head and tail required)
				// Its next points the first node and its prev points to the last node
				// And the last node points to the dummy node
				// dummy.next = first node
				// dummy.prev = last node
	size_t n;
	void remove(Node *w);
	void addBefore(Node *w, T x);
	Node* getNode(size_t i);
public:
	DLList();
	virtual ~DLList();
	size_t size() { return n; }
	T get(size_t i);
	T& operator[](size_t i) { return getNode(i)->x;	}
	const T& operator[](size_t i) const { return getNode(i)->x;	}

	T set(size_t i, T x);
	virtual void add(size_t i, T x);
  T front() { return dummy.next->x; }
  T back() { return dummy.prev->x; }
	void push_back(T x) 	{ add(size(), x); }
	void push_front(T x) 	{ add(0, x); }	
	void remove(size_t i);
	void pop_back() 	{ remove(size()-1); }
	void pop_front() 	{ remove(size_t(0)); }
	virtual void clear();
};

template<class T>
DLList<T>::DLList() {
	dummy.next = &dummy;
	dummy.prev = &dummy;
	n = 0;
}

template<class T>
void DLList<T>::addBefore(Node *w, T x) {
	Node *u = new Node;
	u->x = x;
	u->prev = w->prev;	
	u->next = w;
    // Modify the previous connection to w
	u->next->prev = u; // w->prev=u
	u->prev->next = u; // previous->next points to u
	n++;
}

template<class T>
typename DLList<T>::Node* DLList<T>::getNode(size_t i) {
	Node* p;//=&dummy;
	if (i < n / 2) {	// start from the fist node in forward
		p = dummy.next;	// head node
		for (size_t j = 0; j < i; j++)
			p = p->next;
	} else {  			// start from the lst node in backward
		p = &dummy;		//.prev; // tail node
		for (size_t j = n-i; j > 0; j--)
			p = p->prev;
	}
	return (p);
}


template<class T>
DLList<T>::~DLList() {
	clear();
}

template<class T>
void DLList<T>::clear() {
	Node *u = dummy.next;
	while (u != &dummy) {
		Node *w = u->next;
		delete u;
		u = w;
	}
	n = 0;
}

template<class T>
void DLList<T>::remove(Node *w) {
	w->prev->next = w->next;
	w->next->prev = w->prev;
	delete w;
	n--;
}


template<class T>
T DLList<T>::get(size_t i) {
    return getNode(i)->x;
}

template<class T>
T DLList<T>::set(size_t i, T x) {
	Node* u = getNode(i);
	T y = u->x;
	u->x = x;
	return y;
}

template<class T>
void DLList<T>::add(size_t i, T x) {
    addBefore(getNode(i), x);
}

template<class T>
void DLList<T>::remove(size_t i) {
	Node *w = getNode(i);
	//T x = w->x;
	remove(w);
	//return x;
}


} /* namespace ods */
#endif /* DLLIST_H_ */
