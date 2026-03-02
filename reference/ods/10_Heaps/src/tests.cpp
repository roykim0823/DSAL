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

#include "test_heap.h"
#include "BinaryHeap.h"
#include "MeldableHeap.h"

using namespace ods;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif


int main(int argc, char **argv)
{
	int n = 1000000;

	srand(0);

	{
		cout << endl << "BinaryHeap<int>:" << endl;
		BinaryHeap<int> h;
		heapTests(h, n);
	}

	{
		cout << endl << "MeldableHeap<int>:" << endl;
		MeldableHeap1<int> h;
		heapTests(h, n);
	}

	return 0;
}
