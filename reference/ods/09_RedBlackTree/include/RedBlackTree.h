#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include "BinarySearchTree.h"

namespace ods {

template<class Node, class T> class RedBlackTree;


template<class Node, class T>
class RedBlackNode : public BSTNode<Node, T> {
protected:
	friend class RedBlackTree<Node, T>;
	char colour;	// red=0, black=1
};

template<class Node, class T>
class RedBlackTree : public BinarySearchTree<Node, T> {
protected:
	using BinaryTree<Node>::root;
	using BinaryTree<Node>::nil;
	using BinarySearchTree<Node,T>::n;
	static const int red = 0;
	static const int black = 1;
	void pushBlack(Node *u);
	void pullBlack(Node *u);
	void flipLeft(Node *u);
	void flipRight(Node *u);
	void swapcolours(Node *u, Node *w);
	void addFixup(Node *u);
	void removeFixup(Node *u);
	Node *removeFixupCase1(Node *u);
	Node *removeFixupCase2(Node *u);
	Node *removeFixupCase3(Node *u);
	void verify();
	int verify(Node *u);
	// Declare BST's virtual functions
	virtual Node *findLast(T x);
public:
	RedBlackTree();
	virtual ~RedBlackTree();
	virtual bool add(T x);
	virtual bool remove(T x);
	// Declare BST's virtual functions
	virtual void splice(Node *u);
	virtual void rotateRight(Node *u);
	virtual void rotateLeft(Node *u);
};

template<class T>
class RedBlackNode1 : public RedBlackNode<RedBlackNode1<T>, T> { };

template<class T>
class RedBlackTree1 : public RedBlackTree<RedBlackNode1<T>, T> { };

// node=red, both children=black
template<class Node, class T>
void RedBlackTree<Node,T>::pushBlack(Node *u) {
	u->colour--;
	u->left->colour++;
	u->right->colour++;
}

// node=black, both children=red
template<class Node, class T>
void RedBlackTree<Node,T>::pullBlack(Node *u) {
	u->colour++;
	u->left->colour--;
	u->right->colour--;
}

// if u->right is red, then restore left-leaning property
template<class Node, class T>
void RedBlackTree<Node,T>::flipLeft(Node *u) {
	swapcolours(u, u->right);
	rotateLeft(u);
}

// the reverse of the flipLeft
template<class Node, class T>
void RedBlackTree<Node,T>::flipRight(Node *u) {
	swapcolours(u, u->left);
	rotateRight(u);
}


template<class Node, class T>
void RedBlackTree<Node,T>::swapcolours(Node *u, Node *w) {
	char tmp = u->colour;
	u->colour = w->colour;
	w->colour = tmp;
}



template<class Node, class T>
void RedBlackTree<Node,T>::addFixup(Node *u) {
	while (u->colour == red) {
		if (u == root) { // u is the root - done
			u->colour = black;
			return;
		}

		Node *w = u->parent;
		if (w->left->colour == black) { // ensure left-leaning  (1st condition)
			flipLeft(w);
			u = w;
			w = u->parent;
		}
		if (w->colour == black)
			return; // no red-red edge = done

		// now w->colour is red
		Node *g = w->parent; // grandparent of u
		if (g->right->colour == black) {	// red and red (2nd condition)
			flipRight(g);
			return;
		} else { 	// both g's children are red. (3rd condition)
			pushBlack(g);
			u = g;
		}
	}
}



template<class Node, class T>
void RedBlackTree<Node,T>::removeFixup(Node *u) {
	while (u->colour > black) {
		if (u == root) {
			u->colour = black;
		} else if (u->parent->left->colour == red) {
			u = removeFixupCase1(u);
		} else if (u == u->parent->left) {
			u = removeFixupCase2(u);
		} else {
			u = removeFixupCase3(u);
		}
	}
	if (u != root) { // restore left-leaning property, if needed
		Node *w = u->parent;
		if (w->right->colour == red && w->left->colour == black) {
			flipLeft(w);
		}
	}
}



template<class Node, class T>
Node* RedBlackTree<Node,T>::removeFixupCase1(Node *u) {
	flipRight(u->parent);
	return u;
}



template<class Node, class T>
Node* RedBlackTree<Node,T>::removeFixupCase2(Node *u) {
	Node *w = u->parent;
	Node *v = w->right;
	pullBlack(w); // w->left
	flipLeft(w); // w is now red
	Node *q = w->right;
	if (q->colour == red) { // q-w is red-red
		rotateLeft(w);
		flipRight(v);
		pushBlack(q);
		if (v->right->colour == red)
			flipLeft(v);
		return q;
	} else {
		return v;
	}
}



template<class Node, class T>
Node* RedBlackTree<Node,T>::removeFixupCase3(Node *u) {
	Node *w = u->parent;
	Node *v = w->left;
	pullBlack(w);
	flipRight(w);            // w is now red
	Node *q = w->left;
	if (q->colour == red) { // q-w is red-red
		rotateRight(w);
		flipLeft(v);
		pushBlack(q);
		return q;
	} else {
		if (v->left->colour == red) {
			pushBlack(v); // both v's children are red
			return v;
		} else { // ensure left-leaning
			flipLeft(v);
			return w;
		}
	}
}

template<class Node, class T>
void RedBlackTree<Node,T>::verify() {
	assert (size(root) == n);
	verify(root);
}



template<class Node, class T>
int RedBlackTree<Node,T>::verify(Node *u) {
	if (u == nil)
		return u->colour;
	assert(u->colour == red || u->colour == black);
	if (u->colour == red)
		assert(u->left->colour == black && u->right->colour == black);
	assert(u->right->colour == black || u->left->colour == red);
	int dl = verify(u->left);
	int dr = verify(u->right);
	if (dl != dr)
	return dl + u->colour;
}


template<class Node, class T>
RedBlackTree<Node,T>::RedBlackTree() {
	nil = new Node;
	nil->colour = black;
	root = nil;
}



template<class Node, class T>
RedBlackTree<Node,T>::~RedBlackTree() {
	delete nil;
}

// 1. Perform the standard binary insertion with red color
template<class Node, class T>
bool RedBlackTree<Node,T>::add(T x) {
	Node *u = new Node();
	u->left = u->right = u->parent = nil;
	u->x = x;
	u->colour = red;  	// clolr of new node is red;
	bool added = BinarySearchTree<Node,T>::add(u);
	if (added)
		addFixup(u);	// to maintain the property.
	return added;
}



template<class Node, class T>
bool RedBlackTree<Node,T>::remove(T x) {
	Node *u = findLast(x);
	if (u == nil || compare(u->x, x) != 0)
		return false;
	Node *w = u->right;
	if (w == nil) {
		w = u;
		u = w->left;
	} else {
		while (w->left != nil)
			w = w->left;
		u->x = w->x;
		u = w->right;
	}
	splice(w);
	u->colour += w->colour;
	u->parent = w->parent;
	delete w;
	removeFixup(u);
	return true;
}

// Add declaration of BST's virtual functions
template<class Node, class T>
void RedBlackTree<Node,T>::splice(Node *u) {
    BinarySearchTree<Node, T>::splice(u);
}

template<class Node, class T>
void RedBlackTree<Node,T>::rotateRight(Node *u) {
    BinarySearchTree<Node, T>::rotateRight(u);
}

template<class Node, class T>
void RedBlackTree<Node,T>::rotateLeft(Node *u) {
    BinarySearchTree<Node, T>::rotateLeft(u);
}

template<class Node, class T>
Node* RedBlackTree<Node,T>::findLast(T x) {
    return BinarySearchTree<Node, T>::findLast(x);
}

}  // namespace HKSTL
#endif  // REDBLACKTREE_H_
