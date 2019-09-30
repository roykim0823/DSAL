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

#include "Sort.h"
#include "BinaryHeap.h"

using namespace ods;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

const unsigned RA=0x0001;   // random access
const unsigned FM=0x0002;   // front modifications

void sortTests(int n) {
	clock_t start, stop;
	array<int> a(n);

	for (int i = 0; i < n; i++)
		a[i] = rand();
	cout << "Sorting " << n << " elements using quickSort...";
	cout.flush();
	start = clock();
	quickSort(a);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	for (int i = 1; i < n; i++)
		assert(a[i-1] <= a[i]);

	for (int i = 0; i < n; i++)
		a[i] = rand();
	cout << "Sorting " << n << " elements using heapSort...";
	cout.flush();
	start = clock();
	heapSort(a);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	for (int i = 1; i < n; i++)
		assert(a[i-1] <= a[i]);

	for (int i = 0; i < n; i++)
		a[i] = rand();
	cout << "Sorting " << n << " elements using mergeSort...";
	cout.flush();
	start = clock();
	mergeSort(a);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	for (int i = 1; i < n; i++)
		assert(a[i-1] <= a[i]);

	for (int i = 0; i < n; i++)
		a[i] = rand();
	cout << "Sorting " << n << " elements using radixSort...";
	cout.flush();
	start = clock();
	radixSort(a);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	for (int i = 1; i < n; i++)
		assert(a[i-1] <= a[i]);

}


int main(int argc, char **argv)
{
	int n = 1000000;

	srand(0);

	sortTests(n);
//	sortTests(16);

	return 0;
}

