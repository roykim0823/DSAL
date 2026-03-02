#ifndef _DIJKSTRA_SP
#define _DIJKSTRA_SP

#include "EdgeWeightedDiGraph.h"
#include "indexMinPQ.h"
#include <iostream>
#include <vector>
#include <deque>
#include <limits>

class DijkstraSP {
	int source;
	std::vector<DirectedEdge> edgeTo;
	std::vector<double> distTo;
	IndexMinPQ<double> pq;

	void relax(EdgeWeightedDiGraph G, std::pair<int, double> v)
	{
		std::cout << "relax: " << v.first << std::endl;
     	std::vector<DirectedEdge> adj = G.get_adj(v.first);
     	std::vector<DirectedEdge>::iterator pos;
		for(pos=adj.begin(); pos!=adj.end(); ++pos)
		{
			int w = pos->get_to();
			if(distTo[w] > distTo[v.first] + pos->get_weight()) {
				distTo[w]=distTo[v.first]+pos->get_weight();
				edgeTo[w] = *pos;
				if(pq.contains(w)) 
					pq.changeKey(std::make_pair(w, distTo[w]));
				//else	// Necessary? 
				//	pq.add(std::make_pair(w, distTo[w]));
			}
		}
	}

public:
	DijkstraSP(EdgeWeightedDiGraph G, int s):pq(G.get_V())
	{
		edgeTo.resize(G.get_V());
		distTo.resize(G.get_V());

	    source=s;
		for(int v=0; v<G.get_V(); v++)
			distTo[v]=std::numeric_limits<double>::infinity();
		distTo[s]=0.0;
		//edgeTo[s]=DirectedEdge(0,0,0.0);

		// Initialize priority queue with infinity except for starting node
		for(int v=0; v<G.get_V(); v++) {
			if(v==s) 
				pq.add(std::make_pair(s, 0));
			else
				pq.add(std::make_pair(v, std::numeric_limits<double>::infinity()));
		}

		while(pq.isEmpty()==false) {
			pq.print_pq();
			print_distTo();
			print_edgeTo();
			relax(G, pq.extractMin());
			
		}
		//std::vector<DirectedEdge>::iterator pos=edgeTo.begin();
		//edgeTo.erase(pos);
	}

	double get_distTo(int v) { return distTo[v]; }
	bool hasPathTo(int v)	
	{ 
		return distTo[v] < std::numeric_limits<double>::infinity();
	}

	std::stack<DirectedEdge> pathTo(int v)
	{
		// return path from s to v; null if no such path
		std::stack<DirectedEdge> path;
		if(hasPathTo(v)==false) return path;
		
        DirectedEdge e;
		for(e=edgeTo[v]; e.get_to()!=source && e.get_to()>=0; e=edgeTo[e.get_from()]) 
		//for(e=edgeTo[v]; e.get_to()!=source ; e=edgeTo[e.get_from()]) 
			path.push(e);
		return path;
	}

	void print_distTo()
	{
		std::vector<double>::iterator pos;
		for(pos=distTo.begin(); pos!=distTo.end(); ++pos)
			std::cout << *pos << " ";
		std::cout<<std::endl;
	}

	void print_edgeTo()
	{
		std::vector<DirectedEdge>::iterator pos;
		for(pos=edgeTo.begin(); pos!=edgeTo.end(); ++pos){
			pos->get_DirectedEdge();
			std::cout << " ";
		}
		std::cout<<std::endl;
	}
};

#endif

