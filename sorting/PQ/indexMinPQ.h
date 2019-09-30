#ifndef _INDEXMINPQ
#define _INDEXMINPQ

#include <iostream>
#include <vector>
#include <utility>

template <typename T> 
class IndexMinPQ {
	typedef std::pair<int, T> Item;
	std::vector<Item> pq;		// heap-ordered complete(full) binary tree (1-based)
	std::vector<int> qp;		// inverse: qp[pq[i]] = i
	int N;             			// number of elements

	bool greater(int i, int j)
	{
		return (pq[i].second > pq[j].second);
	}

	void exch(int i, int j)
	{
		int index_t = qp[pq[i].first];
		Item t=pq[i];

		qp[pq[i].first]=qp[pq[j].first];
		pq[i]=pq[j];

		qp[pq[j].first]=index_t;
		pq[j]=t;
	}

	void swim(int k)
	{
		while(k>1 && greater(k/2, k))
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
			if(j<N && greater(j, j+1)) j++;
			if(!greater(k, j)) break;
			exch(k, j);
			k=j;
		}
	}

public:
	IndexMinPQ(int maxN)
	{
		N=0;
		pq.resize(maxN+1);
		qp.resize(maxN+1);
		
		// initialize qp
		std::vector<int>::iterator pos;
		for(pos=qp.begin(); pos!=qp.end(); ++pos)
			*pos=-1;

	}

	bool isEmpty() { return (N==0); }
	int size() { return N; }
	
	void add(std::pair<int, T> v)
	{
		N++;
		qp[v.first]=N;
		pq[N]=v;
		swim(N);
	}

	Item extractMin()
	{
		Item min = pq[1];		// Retrieve max key from top
		exch(1, N--);       // Exchange with last item.
		qp[pq[N+1].first] = -1;
		pq.pop_back();  	// Avoid loitering
		//pq.resize(N);
		
		sink(1);            // Restore heap property
		return min;
	}

	void changeKey(Item item)
	{
		int pq_index=qp[item.first];
		if(pq_index != -1)
		{
			pq[pq_index]=item;	// Change Key
			swim(pq_index);
			sink(pq_index);
		}
	}

	void print_pq()
	{

		typedef typename std::vector<Item>::iterator iter;
		iter pos;
		for(pos=pq.begin(); pos!=pq.end(); ++pos)
			std::cout << "(" << pos->first << ", " << pos->second << ") ";
		std::cout << std::endl;

		std::vector<int>::iterator pos2;
		for(pos2=qp.begin(); pos2!=qp.end(); ++pos2)
			std::cout <<  *pos2 << " ";
		std::cout << std::endl;
	}

	/*
	void changeKey(Item item)
	{
		// Find the element in the index priority queue
		//std::vector<Item>::iterator pos; 	// ERROR in g++
		typedef typename std::vector<Item>::iterator iterator;
		iterator pos;
		int i=0;
		for(pos=pq.begin(); pos!=pq.end(); ++pos)
		{
			if(pos->first == item.first)
			{
				pos->second = item.second;	// change key value
				//swim(pos->first);	// Reheapify
				//sink(pos->first);
				swim(i);	// Reheapify
				sink(i);
			}
			i++;
		}
	}
	*/

};

#endif




		



