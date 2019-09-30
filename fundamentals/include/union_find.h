#ifndef UNION_FIND_H_
#define UNION_FIND_H_

#include <iostream>
#include <vector>

class unionFind {
	std::vector<int> id;	// access to component id
	int count;             	// number of components
protected:
	virtual int find(int p) {
		return id[i];
	}
public:
	unionFind(int n): count(n) {
		id.resize(n);
		for(int i=0; i<n; i++)
			id[i]=i;
	}

	int get_count() 				{ return count; }
	bool connected(int p, int q)	{ return find(p) == find(q); }
	virtual void make_union (int p, int q) = 0;
};

// Complexity
// init: O(n), union: O(n), find: O(1)
// union: O(n^2) to process a sequence of N union commands on N objects
class QuickFindUF : public unionFind // eager approach
{
public:
	QuickFindUF(int n): unionFind(n) {}

	// Put p and q into the same component
	void connect(int p, int q) override final
	{
     	int pID = find(p);
		int qID = find(q);

		// Nothing to do if p and q are already in the same component
		if(pID == qID) return;

		// change all entires with id[i] to id[q];
		std::vector<int>::iterator pos;
		for(pos=id.begin(); pos!=id.end(); ++pos)
			if(*pos==pID) *pos=qID;
		count--;
	}

};


class QuickUnionUF : public unionFind	// lazy approach
{
protected:
	int find(int p) override final { 
		return id[p]; 
	}
public:
	QuickUnionUF(int n): unionFind(n) {}

	// chase parent poiners until reach root
	int root(int p)	override final {
		// depth of i array accesses
		while (p !=id[p]) p=id[p];
		return p; 
	}



	void connect(int p, int q)
	{
		// Put p and q into the same component
     	int pRoot = root(p);
		int qRoot = root(q);

		if(pRoot == qRoot) return;

		// Rename p's component to q's name
		id[pRoot] = qRoot;
		count--;
	}

};


class WeightedQuickUnionUF
{
	std::vector<int> id;	// access to component id 
	std::vector<int> sz;	// size of component for roots  
	int count;				// number of components

public:
	WeightedQuickUnionUF(int N)
	{
		// Initialize component id array
		count = N;
		id.resize(N);
		for(int i=0; i<N; i++)
			id[i]=i;
		sz.resize(N);
		for(int i=0; i<N; i++)
			sz[i]=1;

	}

	int get_count() { return count; }
	
	bool connected(int p, int q) 
	{ 
		return find(p) == find(q);
	}

	int find(int p)	// Find the root
	{ 
		// Find component name
		while (p !=id[p]) 
		{
			id[p] = id[id[p]]; // Path Compression
			p=id[p];
		}
		return id[p]; 
	}

	void connect(int p, int q)
	{
		// Put p and q into the same component
     	int i = find(p);
		int j = find(q);

		if(i == j) return;

		// Rename p's component to q's name
		if(sz[i] < sz[j]) { 
			id[i] = j; sz[j]+=sz[i];
		} else {
			id[j] = i; sz[i]+=sz[j];
		}
		count--;
	}

};

#endif  // UNION_FIND_H_
