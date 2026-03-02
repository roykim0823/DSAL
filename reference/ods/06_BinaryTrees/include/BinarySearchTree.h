/*
 * BinarySearchTree.h
 *
 *  Created on: 2011-11-28
 *      Author: morin
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include <climits>
#include <cmath>
#include "BinaryTree.h"
#include "utils.h"

namespace ods {

template<class Node, class T>
class BSTNode : public BTNode<Node> {
public:
	T x;
};

/**
 * A binary search tree class.  The Node parameter should be a subclass
 * of BSTNode<T> (or match it's interface)
 */
template<class Node, class T>
class BinarySearchTree : public BinaryTree<Node> {
protected:
	using BinaryTree<Node>::root;
	using BinaryTree<Node>::nil;
	int n;
	T null;
	virtual Node *findLast(T x);
	virtual bool addChild(Node *p, Node *u);
	virtual void splice(Node *u);
	virtual void remove(Node *u);
	virtual void rotateRight(Node *u);
	virtual void rotateLeft(Node *u);
	virtual bool add(Node *u);
public:
	BinarySearchTree();
	BinarySearchTree(T null);
	virtual ~BinarySearchTree();
	virtual bool add(T x);
	virtual bool remove(T x);
	virtual T find(T x);
	virtual T findEQ(T x);
	virtual int size();
	virtual void clear();
};

template<class T>
class BSTNode1 : public BSTNode<BSTNode1<T>, T> { };

template<class T>
class BinarySearchTree1 : public BinarySearchTree<BSTNode1<T>, T> {
public:
	BinarySearchTree1();
};


/*
 * FIXME: Why doesn't this work?
template<class Node>
BinarySearchTree<Node,int>::BinarySearchTree()  {
	this->null = INT_MIN;
	n = 0;
}
*/

template<class Node, class T>
BinarySearchTree<Node,T>::BinarySearchTree() {
	this->null = (T)NULL;  // won't work for non-primitive types
	n = 0;
}


template<class Node, class T>
BinarySearchTree<Node,T>::BinarySearchTree(T null) {
	this->null = null;
	n = 0;
}

template<class Node, class T>
Node* BinarySearchTree<Node,T>::findLast(T x) {
	Node *w = root, *prev = nil;
	while (w != nil) {
		prev = w;
		int comp = compare(x, w->x);
		if (comp < 0) {
			w = w->left;
		} else if (comp > 0) {
			w = w->right;
		} else {
			return w;
		}
	}
	return prev;
}

template<class Node, class T>
T BinarySearchTree<Node,T>::findEQ(T x) {
	Node *w = root;
	while (w != nil) {
		int comp = compare(x, w->x);
		if (comp < 0) {
			w = w->left;
		} else if (comp > 0) {
			w = w->right;
		} else {
			return w->x;
		}
	}
	return null;
}

// Return the smallest value of the tree that is greater than or equal to x
template<class Node, class T>
T BinarySearchTree<Node,T>::find(T x) {
	Node *w = root, *z = nil;
	while (w != nil) {
		int comp = compare(x, w->x);
		if (comp < 0) {
			z = w;		// x < w->x, then return w->x that is smallest, but greater than x
			w = w->left;
		} else if (comp > 0) {
			w = w->right;
		} else {
			return w->x;
		}
	}
	return z == nil ? null : z->x;
}

template<class Node, class T>
BinarySearchTree<Node,T>::~BinarySearchTree() {
	// nothing to do - BinaryTree destructor does cleanup
}

template<class Node, class T>
bool BinarySearchTree<Node, T>::addChild(Node *p, Node *u) {
		if (p == nil) {
			root = u;              // inserting into empty tree
		} else {
			int comp = compare(u->x, p->x);
			if (comp < 0) {
				p->left = u;
			} else if (comp > 0) {
				p->right = u;
			} else {
				return false;   // u.x is already in the tree
			}
			u->parent = p;
		}
		n++;
		return true;
}

template<class Node, class T>
bool BinarySearchTree<Node, T>::add(T x) {
	Node *p = findLast(x);
	Node *u = new Node;
	u->x = x;
	return addChild(p, u);
}

template<class Node, class T>
bool BinarySearchTree<Node, T>::add(Node *u) {
	Node *p = findLast(u->x);
	return addChild(p, u);
}

template<class Node, class T>
void BinarySearchTree<Node, T>::splice(Node *u) {
	Node *s, *p;
	// s is the node's child
	if (u->left != nil) {
		s = u->left;
	} else {
		s = u->right;
	}

	if (u == root) { 	// If u is the root.
		root = s;
		p = nil;
	} else {
		p = u->parent;
		// if u is a left, then s is null
		if (p->left == u) { 	// the target is a left child
			p->left = s;
		} else {
			p->right = s;     	// the target is a right child
		}
	}
	// connect s->parent to its parent.
	if (s != nil) {	// if a node is not null node?
		s->parent = p;
	}
	n--;
}

// Complex one
// 1. If u is a leaf, then we can just detach u from its parent.
// 2. If u has only one child, then we can splice u from the tree by having u.parent adopt u's child
// 3. If u has two children. Replace the node from its right child's smallest decedent.
template<class Node, class T>
void BinarySearchTree<Node, T>::remove(Node *u) {
	if (u->left == nil || u->right == nil) { 	// Case 1 or 2
		splice(u);
		delete u;
	} else {  // Case 3
		Node *w = u->right;
		while (w->left != nil)	// search its right child's smallest decedent
			w = w->left;
		u->x = w->x;
		splice(w);
		delete w;
	}
}

template<class Node, class T>
bool BinarySearchTree<Node, T>::remove(T x) {
	Node *u = findLast(x);
	if (u != nil && compare(x, u->x) == 0) {
		remove(u);
		return true;
	}
	return false;
}

template<class Node, class T> inline
int BinarySearchTree<Node, T>::size() {
	return n;
}

template<class Node, class T> inline
void BinarySearchTree<Node, T>::clear() {
	BinaryTree<Node>::clear();
	n = 0;
}

template<class Node, class T>
void BinarySearchTree<Node, T>::rotateLeft(Node *u) {
	Node *w = u->right;
	w->parent = u->parent;
	if (w->parent != nil) {
		if (w->parent->left == u) {
			w->parent->left = w;
		} else {
			w->parent->right = w;
		}
	}
	u->right = w->left;
	if (u->right != nil) {
		u->right->parent = u;
	}
	u->parent = w;
	w->left = u;
	if (u == root) { root = w; root->parent = nil; }
}

template<class Node, class T>
void BinarySearchTree<Node, T>::rotateRight(Node *u) {
	Node *w = u->left;
	w->parent = u->parent;
	if (w->parent != nil) {
		if (w->parent->left == u) {
			w->parent->left = w;
		} else {
			w->parent->right = w;
		}
	}
	u->left = w->right;
	if (u->left != nil) {
		u->left->parent = u;
	}
	u->parent = w;
	w->right = u;
	if (u == root) { root = w; root->parent = nil; }
}



/*
template<class T>
BinarySearchTree1<T*>::BinarySearchTree1() : BinarySearchTree<BSTNode1<T*>, T*>(NULL) {
}
*/

template<class T>
BinarySearchTree1<T>::BinarySearchTree1()  {
}


} /* namespace ods */
#endif /* BINARYSEARCHTREE_H_ */
