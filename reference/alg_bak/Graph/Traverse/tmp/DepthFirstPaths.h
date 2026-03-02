#include <vector>
#include <iostream>
#include "Graph.h"

class DepthFirstPath
{
	vector<bool> marked;
	vector<int> edgeTo;
	int source;

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
			{
				edgeTo[*pos]=v;
				dfs(G, *pos);
		}
		cout << "FINISH dfs(" << v << ")" << endl;
	}

public:
	DepthFirstPath(Graph G, int s=0)
	{
		marked.resize(G.get_V());
		edgeTo.resize(G.get_V());
		source = s;
		dfs(G, s);
	}

	bool hasPathTo(int v)
	{ return marked[v]; }

	stack<int> pathTo(int v)
	{
		if(hasPathTo(v)==false) return NULL;
		stack<int> path;
		for(int x=v; x !=source; x=edgeTo[x])
			path.push(x);
		path.push(source);
		return path;
	}

};
