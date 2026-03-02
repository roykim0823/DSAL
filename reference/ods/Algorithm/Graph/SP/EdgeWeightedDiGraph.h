#ifndef _EDGE_WEIGHTED_DIGRAPH
#define _EDGE_WEIGHTED_DIGRAPH

#include <iostream>
#include <vector>

class DirectedEdge {
	int v;	// one vertx
	int w;	// the other vertex
	double weight;	// edge weight

public:
	DirectedEdge(int v=-1, int w=-1, double weight=0.0)
	{
		this->v = v;
		this->w = w;
		this->weight = weight;
	}

	double get_weight() { return weight; }
	int get_from()	{ return v;	}
	int get_to()	{ return w;	}

	void get_DirectedEdge()
	{
		std::cout << "(" << v << "->" << w << ",W=" << weight <<")";
	}
};

//typedef typename std::vector<DirectedEdge>::iterator iter;

class EdgeWeightedDiGraph
{
	typedef std::vector<DirectedEdge> DiEdge;
	int V;
	int E;
	std::vector<DiEdge> adj;

public:
	EdgeWeightedDiGraph(int V)
	{
		this->V = V;
		this->E = 0;
		adj.resize(V);
	}

	int get_V() { return V; }
	int get_E() { return E; }

	void addEdge(DirectedEdge e)
	{
		adj[e.get_from()].push_back(e);
		E++;
	}

	DiEdge get_adj(int v) { return adj[v]; }

	DiEdge edges()
	{
		DiEdge b;
		for (int v=0; v<V; v++)
		{
			DiEdge::iterator pos;
			for(pos=adj[v].begin(); pos != adj[v].end(); ++pos)
				b.push_back(*pos);
		}
		return b;
	}
	
	void print_graph()
	{
		for (int v=0; v<V; v++)
		{
			std::cout << v << " : ";
			DiEdge::iterator pos;
			for(pos=adj[v].begin(); pos != adj[v].end(); ++pos)
                //cout << "(" <<pos->get_to() << ", " << pos->get_weight() << ") ";
				pos->get_DirectedEdge();
			std::cout << std::endl;
		}
	}

};
#endif
