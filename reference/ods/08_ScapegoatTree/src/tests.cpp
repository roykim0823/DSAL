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
#include <vector>
using namespace std;

#include "test_tree.h"
#include "ScapegoatTree.h"

using namespace ods;

int main(int argc, char **argv)
{
	int n = 1000000;

	{
		cout << endl << "ScapegoatTree<int>:" << endl;
		ScapegoatTree1<int> t;
		btTests(t);
		ssetTests(t, n, 0x0);
	}
	return 0;
}
