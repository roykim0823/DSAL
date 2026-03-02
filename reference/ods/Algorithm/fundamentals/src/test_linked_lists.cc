#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#include "sl_list.h"
#include "sl_list_shared.h"
#include "dl_list.h"
#include "dl_list_shared.h"
using namespace HKSTL;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif 

void print_time(string str, int n, clock_t start, clock_t end) {
  cout << str << "\t" << n << " times takes \t" << ((double)(end-start))/CLOCKS_PER_SEC
       << " secs" << endl;
}

template <typename T>
void Tests(T &as, size_t n=0)
{
  if (n==0)
    n = 64;

  clock_t start, end;
  start = clock();
	for (int i=0; i<n; i++) {
		as.push_back(i);
    assert(as.front()==0);
    assert(as.back()==i);
	}
  end = clock();
  print_time("push_back()", n, start, end);

  start = clock();
	for (int i=0; i<n; i++) {
    assert(as[i] == i);
	}
  end = clock();
  print_time("opeator[]", n, start, end);

  start = clock();
	for(int i=0; i<n; i++)     {
		assert(as.front()==i);
		as.pop_front();
		assert(as.size()==n-1-i);
	}
  end = clock();
  print_time("pop_front()", n, start, end);


  start = clock();
	for(int i=0; i<n; i++) {
		as.push_front(i);
	  assert(as.front()==i);
	  assert(as.back()==0);
	}
  end = clock();
  print_time("push_front()", n, start, end);

  for (int i=0; i<n; i++)
    assert(as[i] == n-1-i);

  start = clock();
	for(int i=0; i<n; i++)     {
		as.pop_back();
	}
  end = clock();
  print_time("pop_back()", n, start, end);
	
	for(int i=0; i<n; i++)  {
		as.push_front(i);
		as.push_back(i);
	}
	cout << "push_*() ->\t";

	for(int i=0; i<n; i++) {
		assert(as.front()==(n-1-i));
		assert(as.back()==(n-1-i));
		as.pop_front();
		as.pop_back();
	}
	cout << "pop_*()" << endl;
}

int main(int argc, char **argv)
{
	size_t n = 10000;

	SLList<int> ssl;
	cout << "SSList<int>: " << n << " size" << endl;
  Tests(ssl, n);
  SLList_SHARED<int> ssl_shared; 
	cout << "SSList_SHARED<int>: " << n << " size" << endl;
  Tests(ssl_shared, n);
	
  DLList<int> dll;
	cout << "DLList<int>: " << n << " size" << endl;
  Tests(dll, n);

  DLList_SHARED<int> dll_shared;
	cout << "DLList_SHARED<int>: " << n << " size" << endl;
  Tests(dll_shared, n);
}
