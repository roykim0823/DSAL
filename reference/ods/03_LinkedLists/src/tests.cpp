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
// #include "SLList.h"  // implementation is not completed for the listTets()
#include "DLList.h"
#include "SEList.h"
//#include "SkiplistList.h"
using namespace ods;

int main(int argc, char **argv) {
	int n = 1000000;
	srand(0);

	// cout << endl << "SLList<int>:" << endl;
	// SLList<int> sll;
	// listTests(sll, n, FM);

	cout << endl << "DLList<int>:" << endl;
	DLList<int> dll;
	listTests(dll, n, FM);

	{
	cout << endl << "SEList<int>:" << endl;
	SEList<int> sel(50);
	listTests(sel, n, FM);
	}

	// {
	// cout << endl << "SkiplistList<int>:" << endl;
	// SkiplistList<int> sel;
	// listTests(sel, n, RA|FM);
	// }

	return 0;
}
