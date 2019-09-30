#ifndef _MAX_HEAP
#define _MAX_HEAP

#include <iostream>
#include <vector>

template <typename T> 
class MaxPQ {
	std::vector<T> pq;		// heap-ordered complete(full) binary tree
	int N;             	// 		in pq[1..N] with pq[0] unused

	bool less(int i, int j)
	{
		return (pq[i] < pq[j]);
	}

	void exch(int i, int j)
	{
		T t=pq[i];
		pq[i]=pq[j];
		pq[j]=t;
	}

	void swim(int k)
	{
		while(k>1 && less(k/2, k))
		{
			exch(k/2, k);
			k=k/2;
		}
	}

	void sink(int k)
	{
		while(2*k<=N)
		{
			int j= 2*k;
			if(j<N && less(j, j+1)) j++;
			if(!less(k, j)) break;
			exch(k, j);
			k=j;
		}
	}

public:
	MaxPQ(int maxN)
	{
		N=0;
		pq.resize(maxN+1);
		//T temp;
		//pq.push_back(temp);
	}

	bool isEmpty() { return (N==0); }
	int size() { return N; }
	
	void add(T v)
	{
		pq[++N]=v;
		swim(N);
		//pq.push_back(v);
		//swim(++N);
	}

	T extractMax()
	{
		T max = pq[1];		// Retrieve max key from top
		exch(1, N--);       // Exchange with last item.
		pq.pop_back();  	// Avoid loitering
		pq.resize(N);
		sink(1);            // Restore heap property
		return max;
	}
};

#endif




		



