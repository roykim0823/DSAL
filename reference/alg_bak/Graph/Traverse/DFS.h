#include <vector>
#include <iostream>
#include <stack>
#include "Graph.h"

class DepthFirstSearch
{
	vector<bool> marked;	// Mark nodes that has been explored
	vector<int> edgeTo;     // last vertex on known path to this vertex
	int source;             // starting node

	void dfs(Graph G, int v)
	{
		marked[v] = true;
		vector<int> temp = G.adj(v);
        vector<int>::iterator pos;
		for(pos=temp.begin(); pos !=temp.end(); ++pos)
		{  
			if(marked[*pos]==false)
			{
				edgeTo[*pos]=v;
				dfs(G, *pos);
			}
		}
	}

	void dfs2(Graph G, int v)
	{
		stack<int> s;
		marked[v]=true;
		s.push(v);
		while(!s.empty())
		{
			int v=s.top();
		  	//edgeTo[v] = v;
			s.pop();

			vector<int> temp = G.adj(v);
        	vector<int>::iterator pos;
			for(pos=temp.begin(); pos !=temp.end(); ++pos)
			{
				if(marked[*pos]==false)
				{
		    		edgeTo[*pos] = v;
					marked[*pos] = true;
					s.push(*pos);
				}
			}
		}
	}

public:
	DepthFirstSearch(Graph G, int s=0)
	{
		marked.resize(G.get_V());
		edgeTo.resize(G.get_V());
		source = s;
		dfs(G, s);
		//dfs2(G, s);
	}

	bool hasPathTo(int v) 	// return true if there a path from s to v
	{ return marked[v]; }

	stack<int> pathTo(int v)	// return path from s to v; null if no such path
	{
		stack<int> path;
		if(hasPathTo(v)==false) return path;
		for(int x=v; x !=source; x=edgeTo[x])
			path.push(x);
		path.push(source);
		return path;
	}

};
