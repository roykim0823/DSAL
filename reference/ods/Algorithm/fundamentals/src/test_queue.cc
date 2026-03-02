#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "queue.h"
using namespace HKSTL;

template <typename T> 
void arrayBasedLists_Tests(T &list, size_t n=0)
{
  if (n==0)
    n = 100000;
	
  cout << "Test Queue::push() " << endl;;
	for(int i=0; i<n; i++) {
		list.push(i);
		assert(list.front()==0);
	  assert(list.back()==(int)i);
	}
	
	cout << "Test Queue::pop() " << endl;;
	for(int i=0; i<n; i++)     {
		assert(list.front()==(int)i);
		list.pop();
		assert(list.size()==n-1-i);
	}
	cout << "-> PASS" << endl;
}

int main(int argc, char **argv)
{
	Queue<int> queue;
  cout << endl << "Queue<int> Test..." << endl;
  arrayBasedLists_Tests(queue);
}

