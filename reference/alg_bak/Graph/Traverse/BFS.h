#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include "Graph.h"

class BreadthFirstSearch
{
	vector<bool> marked;	// Mark node if a shorest path to this vertex is known
	vector<int> edgeTo;     // last vertex on known path to this vertex
	int source;             // starting node

	void bfs(Graph G, int s)
	{
        queue<int> q;
		marked[s] = true; 	// Mark the source
		q.push(s);	       	// and put it on the queue
		while(!q.empty())
		{
			int v = q.front();	// remove next vertex from the queue
			q.pop();
			
			vector<int> temp = G.adj(v);
        	vector<int>::iterator pos;
			for(pos=temp.begin(); pos !=temp.end(); ++pos)
			{  
				if(marked[*pos]==false)	// For every unmarked (not visited) adjacent vertex,
				{
					edgeTo[*pos]=v;    		// 1. Save last edge on a shortest path
					marked[*pos]=true;      // 2. mark it because path is known
					q.push(*pos);           // 3. and add it to the queue
				}
			}
		}
	}
	
	void bfs(DiGraph G, int s)
	{
        queue<int> q;
		marked[s] = true; 	// Mark the source
		q.push(s);	       	// and put it on the queue
		while(!q.empty())
		{
			int v = q.front();	// remove next vertex from the queue
			q.pop();
			
			vector<int> temp = G.adj(v);
        	vector<int>::iterator pos;
			for(pos=temp.begin(); pos !=temp.end(); ++pos)
			{  
				if(marked[*pos]==false)	// For every unmarked adjacent vertex,
				{
					edgeTo[*pos]=v;    		// 1. Save last edge on a shortest path
					marked[*pos]=true;      // 2. mark it because path is known
					q.push(*pos);           // 3. and add it to the queue
				}
			}
		}
	}


public:
	BreadthFirstSearch(Graph G, int s=0)
	{
		marked.resize(G.get_V());
		edgeTo.resize(G.get_V());
		source = s;
		bfs(G, s);
	}
	BreadthFirstSearch(DiGraph G, int s=0)
	{
		marked.resize(G.get_V());
		edgeTo.resize(G.get_V());
		source = s;
		bfs(G, s);
    }
	bool hasPathTo(int v)	// return true if there a path from s to v
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
