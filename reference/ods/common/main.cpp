/*
 * main.cpp
 *
 *  Created on: 2011-11-23
 *      Author: morin
 */
#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>

#include <iostream>
using namespace std;

#include "ArrayStack.h"
#include "FastArrayStack.h"
#include "ArrayDeque.h"
#include "DualArrayDeque.h"
#include "RootishArrayStack.h"
#include "DLList.h"
#include "SEList.h"
#include "SkiplistList.h"

#include "FastSqrt.h"

#include "SkiplistSSet.h"
#include "BinarySearchTree.h"
#include "Treap.h"
#include "ScapegoatTree.h"
#include "RedBlackTree.h"
#include "BTree.h"

#include "BinaryTrie.h"
#include "XFastTrie.h"
#include "YFastTrie.h"

#include "BinaryHeap.h"
#include "MeldableHeap.h"

#include "BinaryTree.h"

#include "ChainedHashTable.h"
#include "LinearHashTable.h"

#include "Algorithms.h"

#include "AdjacencyMatrix.h"
#include "AdjacencyLists.h"

using namespace ods;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

const unsigned RA=0x0001;   // random access
const unsigned FM=0x0002;   // front modifications

template<class Graph1, class Graph2>
void graphCmp(Graph1 &g1, Graph2 &g2) {
	int n = g1.nVertices();
	assert(n == g2.nVertices());
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			assert(g1.hasEdge(i,j) == g2.hasEdge(i,j));
		}
	}
	for (int i = 0; i < n; i++) {
		int j;
		ArrayStack<int> l1, l2;
		g1.outEdges(i, l1);
		g2.outEdges(i, l2);
		for (int i = 0; i < l1.size(); i++) {
			for (j = 0; j < l2.size(); j++)
				if (l1.get(i) == l2.get(j)) break;
			assert(j < l2.size());
		}
		for (int i = 0; i < l2.size(); i++) {
			for (j = 0; j < l1.size(); j++)
				if (l2.get(i) == l1.get(j)) break;
			assert(j < l2.size());
		}
	}
}

template<class Graph1, class Graph2>
void graphTests(Graph1 &g1, Graph2 &g2) {
	int n = g1.nVertices();
	for (int k = 0; k < 50*n*n; k++) {
		int i = rand() % n;
		int j = rand() % n;
		if (i != j) {
			if (g1.hasEdge(i,j)) {
				g1.removeEdge(i,j);
				g2.removeEdge(i,j);
			} else {
				g1.addEdge(i,j);
				g2.addEdge(i,j);
			}
		}
		graphCmp(g1, g2);
	}
}


void sqrtTests() {
	int n = 1 << 30;
	clock_t start, stop;

	cout << "Initializing sqrt tables " << n << " inputs...";
	cout.flush();
	start = clock();
	FastSqrt::init();
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

/*
	cout << "Testing correctness of " << n << " inputs...";
	cout.flush();
	start = clock();
	for (int t = 1; t < n; t++) {
		if ((t & 0xfffff) == 0xfffff)
			cout << "."; cout.flush();
		int x = t;
		int logx = FastSqrt::log(x);
		assert(((1 << logx) & x) != 0);
		assert((((1 << (logx + 1)) - 1) & x) == x);
		double ms = sqrt(x);
		double fss = FastSqrt::sqrt(x);
		assert (fabs(ms - fss) <= 2.0);
	}
	stop = clock();
	cout << "passed!" << endl;
*/

	n = 1 << 27;

	cout << "Computing " << n << " sqrt roots...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		sqrt(i);
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Computing " << n << " FastSqrt::sqrt roots...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		FastSqrt::sqrt(i);
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}







int main(int argc, char **argv)
{
	int n = 1000000;

	srand(0);


	/* {
		for (int i = 1; i < 10; i++) {
			int b = i*10;
			cout << endl << "BTree<int>(" << b << "):" << endl;
			BTree<int> t(b);
			ssetTests(t, n, 0x0);
		}
	} */



	{
		cout << endl << "YFastTrie<int>:" << endl;
		YFastTrie<int> t;
		ssetTests(t, n, 0x0);
	}

	{
		cout << endl << "XFastTrie<int>:" << endl;
		XFastTrie1<int> t;
		ssetTests(t, n, 0x0);
	}

	{
		cout << endl << "BinaryTrie<int>:" << endl;
		BinaryTrie1<int> t;
		ssetTests(t, n, 0x0);
	}



	{
		int n = 20;
		cout << endl << "Graph Tests" << endl;
		AdjacencyMatrix am(n);
		AdjacencyLists al(n);
		graphTests(am, al);
		bfs(al, 0);
		dfs(al, 0);
		dfs2(al, 0);
	}

	sortTests(n);




	{
		cout << endl << "ScapegoatTree<int>:" << endl;
		ScapegoatTree1<int> t;
		btTests(t);
		ssetTests(t, n, 0x0);
	}



	{
		cout << endl << "SkiplistSet<int>:" << endl;
		SkiplistSSet<int> s;
		ssetTests(s, n, 0x0);
	}




	// sqrtTests();


	return 0;
}
