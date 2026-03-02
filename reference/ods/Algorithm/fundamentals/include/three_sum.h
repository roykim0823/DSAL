#ifndef THREE_SUM_H_
#define THREE_SUM_H_

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void print_three_sum(const std::vector<int>& vec, int i, int j, int k, int sum) {
  return;
  std::cout << i << " " << j << " " << k << " -> " 
       << vec[i] << " + " << vec[j] << " + " << vec[k] << " = " << sum << std::endl;
}

int binary_search(const std::vector<int>& vec, int key) {
  int lo = 0;
  int hi = vec.size()-1;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (key < vec[mid])
      hi = mid - 1;
    else if (key > vec[mid])
      lo = mid + 1;
    else
      return mid;
  }
  return -1;
}

// Ver1: brute-force, O(n^3)
// Choose(N 3) = N(N-1)(N-2) / 3! = 1/6 N^3
int cnt_three_sum_v1(const std::vector<int>& vec, int sum) {
  int cnt = 0;
	for (int i=0; i < vec.size()-2; ++i) { 
		for (int j=i+1; j < vec.size()-1; ++j) { 
			for (int k=j+1; k < vec.size(); ++k) { 
				if (vec[i] + vec[j] + vec[k] == sum) { 
          print_three_sum(vec, i, j, k, sum);
          ++cnt;
				} 
			} 
		} 
	} 
	return cnt; 
} 

// Ver2: using binary search after sorting, O(N^2 * logN)
int cnt_three_sum_v2(std::vector<int> vec, int sum) {
  int cnt = 0;
  std::sort(vec.begin(), vec.end());
	for (int i=0; i < vec.size()-2; ++i) { 
		for (int j=i+1; j < vec.size()-1; ++j) { 
      int k = binary_search(vec, sum-(vec[i]+vec[j]));
      if (k != -1 && k > j) {  // only count if i<j<k to avoid double counting
        print_three_sum(vec, i, j, k, sum);
        ++cnt;
			} 
		} 
	} 
	return cnt; 
} 

// Ver2: using binary search after sorting, O(N^2)
int cnt_three_sum_v2a(std::vector<int> vec, int sum) {
  int cnt = 0;
  std::sort(vec.begin(), vec.end());

	for (int i = 0; i < vec.size()-2; i++) {
		int l = i + 1; // index of the first element in the
		int r = vec.size() - 1; // index of the last element
		while (l < r) {
			if (vec[i] + vec[l] + vec[r] == sum) {
        print_three_sum(vec, i, l, r, sum);
				++cnt;
        l++;
        r--;
			}	else if (vec[i] + vec[l] + vec[r] < sum)
				l++;
			else // vec[i] + vec[l] + vec[r] > sum
				r--;
		}
	}
	return cnt;
}

// Ver3: Hashing Based Solution, O(n^2)
int cnt_three_sum_v3(const std::vector<int>& vec, int sum) {
  int cnt = 0;
	for (int i = 0; i < vec.size() - 2; ++i) {
		// Find pair in subarray vec[i+1..n-1]i with sum equal to sum - vec[i]
    std::unordered_set<int> s;
    std::unordered_map<int, int> debug;  // to debug
		int curr_sum = sum - vec[i];
		for (int j = i + 1; j < vec.size() -1; j++) {
			if (s.find(curr_sum - vec[j]) != s.end()) {
        print_three_sum(vec, i, j, debug[curr_sum-vec[j]], sum);
        ++cnt;
			}
			s.insert(vec[j]);
      debug[vec[j]] = j;
		}
	}
	return cnt;
}

#endif  // THREE_SUM_H_ 
