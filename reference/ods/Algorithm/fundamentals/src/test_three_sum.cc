#include "three_sum.h"

using namespace std;

int main() {
  vector<int> input = {30, -40, -20, -10, 40, 0, 10, 5};

  for (int i=0; i<=100; i+=10) {
    int cnt_v1 = cnt_three_sum_v1(input, i);
    int cnt_v2 = cnt_three_sum_v2(input, i);
    int cnt_v2a = cnt_three_sum_v2a(input, i);
    int cnt_v3 = cnt_three_sum_v3(input, i); 
    if (cnt_v1 == cnt_v2 && cnt_v1 == cnt_v2a && cnt_v1 == cnt_v3)
      cout << "Sum = " << i << " -> " << cnt_v1 << endl;
    else 
      cout << "Error at " << i << endl;
  }
	return 0;
}

