#ifndef UNION_FIND_H_
#define UNION_FIND_H_

#include <iostream>
#include <vector>

class UnionFind {
protected:
	std::vector<int> id;	// access to component id
	int cnt;             	// number of components
	virtual int find(int i) {
		return id[i];
	}
public:
	UnionFind(int n): cnt(n) {
		for(int i=0; i<n; ++i)
      id.push_back(i);
	}

	int count() { return cnt; }
	virtual bool find(int p, int q)	{ return find(p) == find(q); }
	virtual void connect (int p, int q) = 0;
  std::vector<int> get_id() { return id; }
};

// init: O(N), union: O(N), find: O(1)
// total union: O(N^2) to process a sequence of N union commands on N objects
class QuickFind : public UnionFind { // eager approach
public:
	QuickFind(int n): UnionFind(n) {}

	// Put p and q into the same component
	void connect(int p, int q) override final {
    if (find(p, q)) return;
    
    int i = find(p);
    int j = find(q);
		// change all entires with id[pID] to id[qID]
		for(auto pos=id.begin(); pos!=id.end(); ++pos) {
			if(*pos==i) {
        *pos=j;
      }
    }
		cnt--;
	}
};

// init: O(N), union: O(N), find: O(N)
class QuickUnion : public UnionFind	{ // lazy approach
protected:
	virtual int root(int i)	{
		// depth of i array accesses
		while (i != id[i]) {
      i=id[i];  // chase parent pointers until reach root
    }
		return i; 
	}

public:
	QuickUnion(int n): UnionFind(n) {}
  
  bool find(int p, int q) override { return root(p) == root(q); }
	
  virtual void connect(int p, int q) override {
    if (find(p, q)) return;

    int i = root(p);
		int j = root(q);
		id[i] = j;  // change root of p to point to root of q
		cnt--;
	}
};

// init: O(N), union: O(logN), find: O(logN)
class WeightedQuickUnion : public QuickUnion {
protected:
	std::vector<int> sz;	// size of component for roots  
public:
	WeightedQuickUnion(int n): QuickUnion(n), sz(n, 1) {}

	void connect(int p, int q) override final {
    if (find(p, q)) return;

    int i = root(p);
		int j = root(q);
    // link root of smaller tree to root of larger tree.
		if(sz[i] < sz[j]) { 
      id[i] = j; sz[j]+=sz[i]; }
		else {
			id[j] = i; sz[i]+=sz[j];
		}
		cnt--;
	}
};

// init: O(N), union: O(lg*N), find: O(lg*N)
// In practice, WQUPC is O(N)
class WQUPC : public WeightedQuickUnion {  // WeightedQuickUnion with Path Compression
protected:
	int root(int i)	override final{
		// depth of i array accesses
		while (i != id[i]) {
      id[i] = id[id[i]];  // path compression!
      i=id[i];  // chase parent pointers until reach root
    }
		return i; 
	}
public:
	WQUPC(int n): WeightedQuickUnion(n) {}
};

#endif  // UNION_FIND_H_
