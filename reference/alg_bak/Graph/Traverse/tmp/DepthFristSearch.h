#include <vector>
#include <iostream>
#include "Graph.h"

//using namespace std;

class DepthFirstSearch
{
	vector<bool> marked;
	int count;
	void dfs(Graph G, int v)
	{
		cout << "START dfs(" << v << ")" << endl;
		marked[v] = true;
		count++;
		vector<int> temp = G.adj(v);
        vector<int>::iterator pos;
		for(pos=temp.begin(); pos !=temp.end(); ++pos)
		{  
			if(marked[*pos]==true)
				cout << "\tCheck: " << *pos << endl;
			if(marked[*pos]==false)
				dfs(G, *pos);
		}
		cout << "FINISH dfs(" << v << ")" << endl;
	}

public:
	DepthFirstSearch(Graph G, int s=0)
	{
		marked.resize(G.get_V());
		dfs(G, s);
	}

	bool get_mark(int w) { return marked[w]; }
	int get_count() { return count;}
};
