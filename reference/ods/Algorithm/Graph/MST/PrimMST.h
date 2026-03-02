#ifndef _PRIM_MST
#define _PRIM_MST

#include "Edge.h"
#include "EdgeWeightedGraph.h"
#include <vector>
#include <queue>
#include <limits>

class IndexWeight
{
	int index;
	double weight;
public:
	IndexWeight(): index(0), weight(0.0) {}
	IndexWeight(const int _id, const double _w): index(_id), weight(_w) {}

	bool operator > (const IndexWight &other)
	{
		return weight > other.weight;
	}

	int get_index() { return index; }
	int get_weight() { return weight; }
	int change_weight(double w) { weight = w; }
};


class PrimMST
{
	vector<Edge> edgeTo;	// shortest edge from tree vertex
	vector<double> distTo;	// distTo[w] = edgeTo[w].weight()
	vector<bool> marked;    // true if v on tree
	// Eligible crossing edges
	priority_queue<IndexWeight, std::vector<IndexWeight>, std::greater<IndexWeight> > pq;

	void visit(EdgeWeightedGraph G, int v)
	{
		// Add v to tree; update data structures;
		pq.pop();
		marked[v] = true;
		
		vector<Edge>::iterator pos;
		for(pos=G.adj(v).begin(); pos != G.adj(v).end(); ++pos)
		{
			int w = pos->other(v);
			if(marked[w]==true)	continue;	// v-w is ineligible
			if (pos->weight() < distTo[w])
			{
				// Edge e is new best connection from tree to w
				edgeTo[w] = *pos;
				distTo[w] = pos->weight();
				vector<IndexWeight>::iterator pos;
				bool edgeCotains=false;
				for(pos=pq.begin(); pos!=pq.end(); ++pos)
				{
					if(pos->get_index())
					{
						edgeContaions = true;
						pos->change_weight(distTo[w]);
						break;
					}
				}
				if(edgeContatins == false)
				{
					IndexWeight t(w, distTo[w]);
					pq.push(w);
				}
			}
		}
	}

public:
	PrimMST(EdgeWeightedGraph G)
	{
		edgeTo.resize(G.get_V());
		distTo.resize(G.get_V());
		marked.resize(G.get_V());

		for(int v=0; v<G.get_V(); v++)
			// Initialize ditance to Infinity
			distTo[v] = std::numberic_limits<double>::infinity();
		
		distTo[0] = 0.0;
		pq.push(0, 0.0);    // Initialize pq with 0, weight 0.0
		while (!pq.empty()) 
			// Add closest vertex to tree
			visit(G, pq.top());	// vist(G, pg.extramMin());
	}

	vector<Edge> edges()
	{
		vector<Edge> mst;
		for(int v=1; v<eggeTo.size(); v++
			mst.push_back(edgeTo[v]);
		return mst;
	}

	double weight() 
	{
	}

};

		

