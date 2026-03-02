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

template<class Heap>
void heapTests(Heap &h, int n) {
	clock_t start, stop;
	cout << "Adding " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		h.add(rand()%100);
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Removing " << n << " elements...";
	cout.flush();
	start = clock();
	int p = h.remove();
	for (int i = 1; i < n; i++) {
		assert(h.size() == n-i);
		int q = h.remove();
		assert(p <= q);
		p = q;
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}