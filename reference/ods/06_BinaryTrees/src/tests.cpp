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
#include "BinaryTree.h"
#include "BinarySearchTree.h"

using namespace ods;

int main(int argc, char **argv)
{
	int n = 1000000;



	{
		cout << endl << "BinaryTree:" << endl;
		BinaryTree<BTNode1> t;
		btTests(t);
	}

	cout << endl << "BinarySearchTree<int>:" << endl;
	BinarySearchTree1<int> t;
	btTests(t);
	ssetTests(t, n, 0x0);

		{
		BinarySearchTree<BSTNode1<int>,int> s;
		btTests(s);
		ssetTests(s, n, 0x0);
	}

	return 0;
}
