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
#include "SkiplistList.h"
using namespace ods;

int main(int argc, char **argv) {
	int n = 1000000;
	srand(0);

	{
	cout << endl << "SkiplistList<int>:" << endl;
	SkiplistList<int> sel;
	listTests(sel, n, RA|FM);
	}

	return 0;
}
