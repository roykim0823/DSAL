#ifndef _FLOW_NETWORK
#define _FLOW_NETWORK

#include <iostream>
#include <vector>
#include <string>
#include "FlowEdge.h"

class FlowNetwork {
	const int V;	
	int E;

public:
	std::vector<std::vector<FlowEdge> > adj;
	FlowNetwork(int V, int E=0): V(V)
	{
		this->E = E;
		adj.resize(V);
	}

    void addEdge(FlowEdge e) {
		E++;
		int v = e.from();
		int w = e.to();
		FlowEdge e2(w, v, e.get_capacity(), e.get_flow());
		adj[v].push_back(e);
		adj[w].push_back(e);
		//adj[w].push_back(e2);
	}
		
	int get_V() { return V; 	}
	int get_E()	{ return E; 	}

	// return list of edges incident to v
	std::vector<FlowEdge> get_adj(int v) { return adj[v]; }

	// return list of all edges - excludes self loops
	std::vector<FlowEdge> edges() { 
		std::vector<FlowEdge> list;
		for(int v=0; v<V; v++) {
			std::vector<FlowEdge>::iterator pos;
			for(pos=adj[v].begin(); pos!=adj[v].end(); ++pos) {
				if(pos->to() != v)
					list.push_back(*pos);
			}
		}
		return list;
	}

	// String representation of Graph (excludes self loops), O(n^2)
	void print() {
		std::cout << "V=" << V << ", E=" << E << std::endl;
		for(int v=0; v<V; v++) {
			std::vector<FlowEdge>::iterator pos;
			for(pos=adj[v].begin(); pos!=adj[v].end(); ++pos) {
				if(pos->to() != v)
					pos->print();
			}
			std::cout<<std::endl;
		}
	}
	
	void print_all() {
		std::cout << "V=" << V << ", E=" << E << std::endl;
		for(int v=0; v<V; v++) {
			std::vector<FlowEdge>::iterator pos;
			for(pos=adj[v].begin(); pos!=adj[v].end(); ++pos) {
					pos->print();
			}
			std::cout<<std::endl;
		}
	}
};

#endif
		



			
	


