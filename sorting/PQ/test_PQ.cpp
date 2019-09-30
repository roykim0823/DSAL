#include <iostream>
#include "maxPQ.h"
#include "minPQ.h"
#include "indexMinPQ.h"

using namespace std;

int main()
{
	char input[11] = {'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
	MaxPQ<char> test(11);
	MinPQ<char> test2(11);
	IndexMinPQ<char> test3(11);

	for(int i=0; i<11; i++)
	{
		test.add(input[i]);
		test2.add(input[i]);
		test3.add(make_pair(i, input[i]));
		cout << input[i] << " ";
	}
	cout << endl;

	///*
	while(!test.isEmpty())
		cout << test.extractMax() << ' ';
	cout << endl;

	while(!test2.isEmpty())
		cout << test2.extractMin() << ' ';
	cout << endl;
	//*/
	
	test3.print_pq();
	test3.changeKey(make_pair(6, 'Z'));
	test3.print_pq();
	test3.changeKey(make_pair(4, 'C'));
	test3.print_pq();
	
	return 0;
}

	


