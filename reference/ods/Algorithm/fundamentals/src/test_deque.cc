#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "deque.h"
using namespace HKSTL;

template <typename T> 
void arrayBasedLists_Tests(T &list, size_t n=0)
{
  if (n==0)
    n = 100000;
	
  cout << "Test Deque::push_back() " << endl;;
	for(int i=0; i<n; i++) {
		list.push_back(i);
		assert(list.front()==0);
	  assert(list.back()==(int)i);
	}
	
	cout << "Test Deque::pop_front() " << endl;;
	for(int i=0; i<n; i++)     {
		assert(list.front()==(int)i);
		list.pop_front();
		assert(list.size()==n-1-i);
	}

  cout << "Test Deque::push_front() " << endl;;
  for(int i=0; i<n; i++) {
    list.push_front(i);
  }

  cout << "Test Deque::pop_back() " << endl;;
  for(int i=0; i<n; i++) {
    assert(list.back()==i);
    list.pop_back();
    assert(list.size()==n-1-i);
  }
  
  cout << "Test Deque::push_*() " << endl;;
  for(int i=0; i<n; i++) {
    list.push_front(i);
    list.push_back(i);
  }
  
  cout << "Test Deque::pop_*() " << endl;;
  for(int i=0; i<n; i++) {
    assert(list.front()==n-1-i);
    assert(list.back()==n-1-i);
    list.pop_front();
    list.pop_back();
    assert(list.size()==2*(n-1-i));
  }
}

int main(int argc, char **argv)
{
	Deque<int> deque;
  cout << endl << "Deque<int> Test..." << endl;
  arrayBasedLists_Tests(deque);
}

