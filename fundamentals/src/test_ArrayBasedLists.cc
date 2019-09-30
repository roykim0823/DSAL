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

#include "array.h"
#include "vector.h"
//#include "FastArrayStack.h"
//#include "ArrayDeque.h"
//#include "DualArrayDeque.h"
//#include "RootishArrayStack.h"

using namespace HKSTL;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

const unsigned RA=0x0001;   // random access
const unsigned FM=0x0002;   // front modifications

template <class List>
void listTests(List &ell, int n, unsigned flags)
{
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(5);

	ell.clear();

	clock_t start, stop;
	cout << "push_back()\t" << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) 
		ell.push_back(i);

	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	if (flags & RA) {
		cout << "reading\t" << n << " elements...";
		cout.flush();
		start = clock();
		for (int i = 0; i < n; i++)
			assert(ell[i] == i);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

		cout << "insert(i, 2*i)\t" << n << " elements...";
		cout.flush();
		start = clock();
		for (int i = 0; i < n; i++) 
			ell.insert(i, 2*i);
    
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	} else {
		cout << "reading 2log(" << n << ") elements...";
		cout.flush();
		start = clock();
		for (int i = 1; i < n; i*=2) {
			assert(ell[i] == i);
			assert(ell[n-i-1] == n-i-1);
		}
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

		cout << "insert() 2log(" << n << ") elements...";
		cout.flush();
		start = clock();
		for (int i = 1; i < n; i*=2) {
			ell.insert(i, 2*i);
			ell.insert(n-i-1, 2*(n-i-1));
		}
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	}

	if (flags & FM) {
		cout << "insert(0, i)\t" << n << " elements at front...";
		cout.flush();
		start = clock();
		for (int i = 0; i < n; i++)
			ell.insert(0, i);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

		cout << "erase(0)\t" << n << " elements at front...";
		cout.flush();
		start = clock();
		for (int i = 0; i < n; i++)
			ell.erase(0);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	} else {
		cout << "insert(0, i)\tlog(" << n << ") elements at front...";
		cout.flush();
		start = clock();
		for (int i = 1; i < n; i*=2)
			ell.insert(0, i);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

		cout << "erase(0)\tlog(" << n << ") elements at front...";
		cout.flush();
		start = clock();
		for (int i = 1; i < n; i*=2)
			ell.erase(0);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	}

	cout << "erase() backward\t" << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++)
		ell.erase(ell.size()-1);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}


int main(int argc, char **argv)
{
  int n = 100000;
  //int n = 512;

	srand(0);

	Array<int> as;
	cout << endl << "Array<int>: RA test" << endl;
	listTests(as, n, RA);
	cout << endl << "Array<int>: FM test" << endl;
	listTests(as, n, FM);
	
	Vector<int> vs;
	cout << endl << "Vector<int>: RA test" << endl;
	listTests(vs, n, RA);
	cout << endl << "Vector<int>: FM test" << endl;
	listTests(vs, n, FM);
	
  return 0;
}

