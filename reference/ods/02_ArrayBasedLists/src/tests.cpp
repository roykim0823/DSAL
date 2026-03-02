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


#include "test_list.h"
#include "ArrayStack.h"
#include "FastArrayStack.h"
#include "ArrayDeque.h"
#include "DualArrayDeque.h"
#include "RootishArrayStack.h"
using namespace ods;

int main(int argc, char **argv) {
	int n = 1000000;
	srand(0);

	cout << endl << "ArrayStack<int>:" << endl;
	ArrayStack<int> as;
	listTests(as, n, RA);

	cout << endl << "FastArrayStack<int>:" << endl;
	FastArrayStack<int> fas;
	listTests(fas, n, RA);

	cout << endl << "ArrayDeque<int>:" << endl;
	ArrayDeque<int> ad;
	listTests(ad, n, RA|FM);

	cout << endl << "DualArrayDeque<int>:" << endl;
	DualArrayDeque<int> dad;
	listTests(dad, n, RA|FM);

	cout << endl << "RootishArrayStack<int>:" << endl;
	RootishArrayStack<int> ras;
	listTests(ras, n, RA);

	return 0;
}
