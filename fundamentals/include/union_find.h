#ifndef UNION_FIND_H_
#define UNION_FIND_H_

#include <iostream>
#include <vector>

class UnionFind {
protected:
	std::vector<int> id;	// access to component id
	int cnt;             	// number of components
	virtual int find(int i) {
		return id[i];  // component identifier for i (0 to N-1)
	}
public:
	UnionFind(int n): cnt(n) {
		for(int i=0; i<n; ++i)
      id.push_back(i);
	}

	int count() { return cnt; }
	// virtual bool find(int p, int q)	{ return find(p) == find(q); }
	virtual void connect (int p, int q) = 0;
    std::vector<int> get_id() { return id; }
};

// init: O(N), union: O(N), find: O(1)
// total union: O(N^2) to process a sequence of N union commands on N objects
class QuickFind : public UnionFind { // Eager approach
public:
	QuickFind(int n): UnionFind(n) {}

	// Put p and q into the same component
	void connect(int p, int q) override final {
    int pid = id[p];
    int qid = id[q];

		if (pid == qid) return;
	
		// change all entires with id[pID] to id[qID], O(N)
		for(auto pos=id.begin(); pos!=id.end(); ++pos) {
			if(*pos==pid) {
       	*pos=qid;
      }
    }
		cnt--;
	}
};

// init: O(N), union: O(N), find: O(N)
class QuickUnion : public UnionFind	{ // Lazy approach
protected:
  // O(N) worst case when depth of tree is N-1 (N union commands on N objects)
	virtual int root(int i)	{
		// depth of i array accesses
		while (i != id[i]) {
      i=id[i];  // chase parent pointers until reach root
    }
		return i; 
	}

public:
	QuickUnion(int n): UnionFind(n) {}
  
  //bool find(int p, int q) override { return root(p) == root(q); }
	virtual int find(int i) override final { return root(i); }
  virtual void connect(int p, int q) override {
    int pid = root(p);
		int qid = root(q);
		if (pid == qid) return;

		id[pid] = qid;  // change root of p to point to root of q
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
    int pid = root(p);
		int qid = root(q);

		if (pid == qid) return;
		
    // link root of smaller tree to root of larger tree.
		if(sz[pid] < sz[qid]) { 
      id[pid] = qid; sz[qid]+=sz[pid]; }
		else {
			id[qid] = pid; sz[pid]+=sz[qid]; }
		
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