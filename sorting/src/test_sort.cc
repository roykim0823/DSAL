#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>

using namespace std;

#include "sort.h"
#include "priority_queue.h"
using namespace HKSTL;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

void sortTests(vector<int> data, SortType sort_type, std::string str, int n = 0) {

  clock_t start, stop;
  cout << "Sorting " << data.size() << " elements using ";
  cout << str << "...\t\t";

  cout.flush();
  start = clock();
  Sort(data, sort_type, n);
  stop = clock();
  cout << "DONE in (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
  for (int i = 1; i < data.size(); ++i) {
    assert(data[i-1] <= data[i]);
  }
}


void heapsortTests(vector<int> data) {

  clock_t start, stop;
  cout << "Sorting " << data.size() << " elements using HeapSort...\t\t";

  cout.flush();
  start = clock();
  Heap<int>::sort(data);
  stop = clock();
  cout << "DONE in (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
  for (int i = 2; i < data.size(); ++i) {
    assert(data[i-1] <= data[i]);
  }
}

void bucketsortTests(vector<float> data) {
  clock_t start, stop;
  cout << "Sorting " << data.size() << " elements using BucketSort...\t\t";

  cout.flush();
  start = clock();
  BucketSort(data);
  stop = clock();
  cout << "DONE in (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
  for (int i = 2; i < data.size(); ++i) {
    assert(data[i-1] <= data[i]);
  }
}

int main(int argc, char **argv) {
  int n = 10000;
  srand(0);

  vector<int> input;
  for (int i=0; i<n; ++i)
    input.push_back(rand());

  sortTests(input, SortType::Select, "SelectSort");
  sortTests(input, SortType::Insert, "InsertionSort");
  sortTests(input, SortType::Shell, "ShellSort");
  sortTests(input, SortType::Merge, "MergeSort");
  sortTests(input, SortType::Quick2WP, "QuickSort2WP");
  sortTests(input, SortType::Quick, "QuickSort3WP");
  heapsortTests(input);

  vector<int> input_with_range;
  for (int i=0; i<n; ++i) 
    input_with_range.push_back(rand() % (n/10));

  sortTests(input_with_range, SortType::CountSort, "CountSort", n/10);
  sortTests(input_with_range, SortType::RadixSort, "RadixSort");
  sortTests(input_with_range, SortType::PigeonholeSort, "PigeonholeSort");

  vector<float> input_dis;
  std::default_random_engine e;
  std::uniform_real_distribution<> dis(0, 1); // rage 0 - 1

  for (int i=0; i<n; i++)
    input_dis.push_back(dis(e));
  bucketsortTests(input_dis);

  return 0;
}