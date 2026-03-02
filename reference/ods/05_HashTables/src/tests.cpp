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

#include "test_hash.h"
#include "ChainedHashTable.h"
#include "LinearHashTable.h"

using namespace ods;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif


template <class USet>
void unittest(USet &us, int n) {
	clock_t start, stop;
	cout << "Adding " << n << " elements...";
	cout.flush();
	start = clock();
	vector<int> data;

	// Add
	for (int i = 0; i < n; i++) {
		//int input = rand() % (2*n);
		//if(us.add(input))
		us.add(i);
		//	data.push_back(input);

	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Finding " << n << " elements...";
	cout.flush();
	start = clock();
	//int success = 0;

	// Find
	for (int i = 0; i < n; i++) {
//		cout << "find: " << i << " size: " << us.size() << endl;
		assert(us.find(i)!=-1);
	}
	stop = clock();
	//cout << "done [" << success << "/" << n << " (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
 //   cout << "NOT Finding " << n << " elements...";
 	/*
	for (int i = 0; i < n; i++) {
		assert(us.find(i+n)==-1);  	// worst case O(n)
	}
	*/

	cout << "Removing " << n << " elements...";
	cout.flush();
	start = clock();

	// Remove
	for (int i = 0; i < n; i++) {
		assert(us.find(i)!=-1);
		assert(us.remove(i)==true);
    	assert(us.find(i)==-1); 	// worst case O(n)
  //  	cout << "remove: " << i << " size: " << us.size() << endl;
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Final size is " << us.size() << endl;

	cout << "Clearing " << us.size() << " elements...";
	cout.flush();
	start = clock();
	us.clear();
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}


int main(int argc, char **argv)
{
	int n = 1000000;

	cout << endl << "ChainedHashTable<int>:" << endl;
	ChainedHashTable<int> c;
	unittest(c, n);
	hashTests(c, n);

	cout << endl << "LinearHashTable<int>:" << endl;
	LinearHashTable<int> l;
	unittest(l, n);
	hashTests(l, n);
	return 0;
}
