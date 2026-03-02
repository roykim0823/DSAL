#ifndef _EDGE_WEIGHTED_GRAPH
#define _EDGE_WEIGHTED_GRAPH

#include <vector>

class EdgeWeightedGraph
{
	int V;
	int E;
	vector<vector<Edge> > adj;

public:
	EdgeWeightedGraph(int V)
	{
		this->V = V;
		this->E = 0;
		adj.resize(V);
	}

	public int get_V() { return V; }
	public int get_E() { return E; }

	void addEdge(Edge e)
	{
		int v = e.either(), w = e.other(v);
		adj[v].add(e);
		adj[w].add(e);
		E++;
	}

	std::vector<Edge> get_adj(int v)
	{
		return adj[v]; 
	}

	std::vecor<Edge> edges()
	{
		std:vector<Edge> b;
		for (int v=0; v<V; v++)
			vector<Edge>::iterator pos;
			for(pos=adj[v].begin(); pos != adj[v].end(); ++pos)
				if(e.other(v0 > v) b.add(e);
		return b;
	}

}

#endif
