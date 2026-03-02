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

#include "Graph.h"
#include "GraphTraversal.h"

using namespace mySTL;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

template<typename Graph1, typename Graph2>
void graphCmp(Graph1 &g1, Graph2 &g2) {
	int n = g1.nVertices();
	assert(n == g2.nVertices());
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			assert(g1.hasEdge(i,j) == g2.hasEdge(i,j));
		}
	}
	for (int i = 0; i < n; i++) {
		size_t j; vector<int> l1, l2;
		g1.outEdges(i, l1);
		g2.outEdges(i, l2);
		for (size_t i = 0; i < l1.size(); i++) {
			for (j = 0; j < l2.size(); j++)
				if (l1[i] == l2[j]) break;
			assert(j < l2.size());
		}
		for (size_t i = 0; i < l2.size(); i++) {
			for (j = 0; j < l1.size(); j++)
				if (l2[i] == l1[j]) break;
			assert(j < l2.size());
		}
	}
}

template<typename Graph1, typename Graph2>
void genGraph(Graph1 &g1, Graph2 &g2) {
	int n = g1.nVertices();
	for (int k = 0; k < n*n; k++) {
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
	}
}

int main(int argc, char **argv)
{
	srand(0);

   	//int n = 1000;
	int n = 20;
   	cout << endl << "Graph Tests" << endl;
   	AdjMatrix am(n);
   	AdjList<int> al(n);
	cout << "generate Graphs..." << endl;
   	genGraph(am, al);
	cout << "compare Graphs..." << endl;
	graphCmp(am, al);
	cout << "traverse Graph1..." << endl;
   	bfs(am, 0);
  	dfs(am, 0);
  	dfs2(am, 0);

	cout << "traverse Graph2..." << endl;
   	bfs(al, 0);
  	dfs(al, 0);
  	dfs2(al, 0);

	return 0;
}
