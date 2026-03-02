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

#include "test_tree.h"
#include "BinaryTrie.h"
#include "XFastTrie.h"
#include "YFastTrie.h"

using namespace ods;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif


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
	}
		*/
	{
		cout << endl << "BinaryTrie<int>:" << endl;
		BinaryTrie1<int> t;
		ssetTests(t, n, 0x0);
	}

	// Compilation fail
	{
		cout << endl << "XFastTrie<int>:" << endl;
		XFastTrie1<int> t;
		ssetTests(t, n, 0x0);
	}
	{
		cout << endl << "YFastTrie<int>:" << endl;
		YFastTrie<int> t;
		ssetTests(t, n, 0x0);
	}



	return 0;
}
