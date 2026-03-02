#ifndef _FORD_FULKERSON
#define _FORD_FULKERSON

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include "FlowNetwork.h"

class FordFulkerson {
	std::vector<bool> marked;	// marked[v] = true if s->v path in resudual graph
	std::vector<FlowEdge> edgeTo; // edgeTo[v] = last edge on shortest residual s->v path
	double value;	// current value of max flow
	std::vector<std::pair<int, int> > loc;

	// is there an augmenting path?
	// if so, upon termination edgeTo[] will contain a parent-link
	// 		representation of such a path
	bool hasAugmentingPath(FlowNetwork &G, int s, int t) {
		edgeTo.clear();
		marked.clear();
		loc.clear();
		edgeTo.resize(G.get_V());
		marked.resize(G.get_V());
		loc.resize(G.get_V());

		std::cout << "before, marked[t]=" << marked[t] << std::endl;

		// BFS
		std::queue<int> q;
		marked[s] = true; 	// mark the source
		q.push(s);         	// put it on the queue
		while(!q.empty()) {
			int v = q.front();	// remove next vertex from the queue
			q.pop();
			std::cout << "v: "<< v << std::endl;

			//std::vector<FlowEdge> temp = G.get_adj(v);
			std::vector<FlowEdge>::iterator pos;
			int i=0;
			//for(pos=temp.begin(); pos!=temp.end(); ++pos) {
			for(pos=G.adj[v].begin(); pos!=G.adj[v].end(); ++pos) {
				int w = pos->other(v);
				std::cout << "w: "<< w << ", resisualCap: " << pos->residualCapacityTo(w)<< std::endl;

				// if residual capacity from v to w
				if(pos->residualCapacityTo(w) > 0.0) {
					if(marked[w]==false) {
						edgeTo[w] = *pos;
						marked[w] = true;
						std::cout << "mark[" << w << "] is Updated\n";
						q.push(w);
						loc[w]=std::make_pair(v, i);
					}
				}
				i++;
			}
			std::cout << std::endl;
		}
		// is there an augmenting path?
		std::cout << "after, marked[t]=" << marked[t] << std::endl;
		return marked[t];
	}

public:
	FordFulkerson(FlowNetwork &G, int s, int t) {
		/*
		if(s==t) {
			std::cerr << "Source equals sink." << std::endl;
		}
		value = excess(G, t);
		if(isFeasible(G, s, t) == false) {
			std::cerr << "Intitial flow in inseasible." << std::endl;
		}
		*/
		value = 0.0;
		while(hasAugmentingPath(G, s, t)) {
			// compute bottleneck capacity;
			double bottle = std::numeric_limits<double>::infinity();
			for(int v=t; v!=s; v=edgeTo[v].other(v)) {
				std::cout << "for v= " << v << ", next=" << edgeTo[v].other(v)<< std::endl;
			   	int index_adj = loc[v].first;
			   	int inner_index = loc[v].second;
				if(bottle>edgeTo[v].residualCapacityTo(v)) {
				//if(bottle>G.adj[index_adj][inner_index].residualCapacityTo(v)) {
					std::cout << "bottle= " << bottle << ", Rcap= " << edgeTo[v].residualCapacityTo(v) << std::endl;
					bottle=edgeTo[v].residualCapacityTo(v);
					//bottle=G.adj[index_adj][inner_index].residualCapacityTo(v);
				}
			}

			// augment flow
			for(int v=t; v!=s; v=edgeTo[v].other(v)) {
			   //edgeTo[v].addResidualFlowTo(v, bottle);
			   int index_adj = loc[v].first;
			   int inner_index = loc[v].second;
			   std::cout << "AF: " << index_adj << ", " << inner_index << std::endl;
			   edgeTo[v].print();
			   G.adj[index_adj][inner_index].print();
			   G.adj[index_adj][inner_index].addResidualFlowTo(v, bottle);
			   G.adj[index_adj][inner_index].print();

			}

			value += bottle;
			std::cout << "VALUE=" << value << std::endl << std::endl;
			G.print_all();
		}
	}

	double get_value() { return value; }
	bool inCut(int v) { return marked[v]; }

};

#endif


