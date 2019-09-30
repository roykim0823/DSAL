#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "array.h"
#include "vector.h"
using namespace HKSTL;

template <typename T> 
void arrayBasedLists_Tests(T &list, size_t n=0)
{
  if (n==0)
    n = 100000;

	cout << "push_back() " << endl;;
	for(size_t i=0; i<n; i++) {
		list.push_back(i);
		assert(list.size()==i+1);
	}
	for(size_t i=0; i<n; i++)
		assert(list[i]==(int)i);
	
	cout << "reverse() " << endl;
	list.reverse();
	for(size_t i=0; i<n; i++)
		assert(list[i]==(int)(n-1-i));
	
	cout << "pop_back() " << endl;
	for(size_t i=0; i<n; i++)     {
		list.pop_back();
		assert(list.size()==n-1-i);
	}
	
	cout << "insert() " << endl;;
	for(size_t i=0; i<n; i++) {
		list.insert(0,i);
		assert(list.size()==i+1);
	}
	list.reverse();
	for(size_t i=0; i<n; i++)
		assert(list[i]==(int)i);
	
	cout << "erase() " << endl;
	for(size_t i=0; i<n; i++)     {
		list.erase(0);
		assert(list.size()==n-1-i);
	}
	
	cout << "insert() at the end" << endl;;
	for(size_t i=0; i<n; i++) {
		list.insert(i,i);
		assert(list.size()==i+1);
	}
	for(size_t i=0; i<n; i++)
		assert(list[i]==(int)i);
}

int main() {
  Array<int> as;
  cout << endl << "Array<int> Test..." << endl;
  arrayBasedLists_Tests(as);
}
