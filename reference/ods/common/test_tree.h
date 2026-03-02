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

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

template<class Tree>
void btTests(Tree &t) {
	t.size();
	t.size2();  // calculate size by an iterative way
	t.height();
	t.bfTraverse();
	t.traverse();
	t.traverse2();
}

template <class SSet>
void ssetTests(SSet &ss, int n, unsigned flags) {
	clock_t start, stop;
	cout << "Adding " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		ss.add(rand());
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Finding " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		int z = rand();
		int y = ss.find(z);
		if (i % 300000 == 0) {
			cout << "[" << z << "=>" << y << "]";
		}
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Removing " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		ss.remove(rand());
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Final size is " << ss.size() << endl;

	cout << "Clearing " << ss.size() << " elements...";
	cout.flush();
	start = clock();
	ss.clear();
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}