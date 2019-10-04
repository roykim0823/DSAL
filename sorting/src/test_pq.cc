#include <iostream>

using namespace std;

#include "priority_queue.h"
#include "indexMinPQ.h"
using namespace HKSTL;

int main() {
  std::vector<char> input = {'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

  PriorityQueue<char> max_pq(11);
  PriorityQueue<char, std::greater<>> min_pq(11);
  IndexMinPQ<char> index_pq(11);

  for(int i=0; i<11; i++) {
    max_pq.push(input[i]);
    min_pq.push(input[i]);
    index_pq.add(make_pair(i+1, input[i]));
    cout << input[i] << " ";
  }
  cout << endl;

  while(!max_pq.isEmpty()) {
    cout << max_pq.top() << ' ';
    max_pq.pop();
  }
  cout << endl;

  while(!min_pq.isEmpty()) {
    cout << min_pq.top() << ' ';
    min_pq.pop();
  }
  cout << endl;

  std::vector<char> heap_input = // [0] is dummy
  { ' ','S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
  Heap<char>::sort(heap_input);
  for (int i=1; i<heap_input.size(); ++i)
    cout << heap_input[i] << " ";
  cout << endl;
  
  index_pq.print_pq();
  index_pq.changeKey(make_pair(6, 'Z'));
  index_pq.print_pq();
  index_pq.changeKey(make_pair(4, 'C'));
  index_pq.print_pq();
  return 0;
}
