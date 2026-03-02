#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include "Graph.h"

class Cycle {
protected:
	std::vector<bool> marked;	// visited
	bool hasCycle = false;
	UniGraph& graph;

public:
	Cycle(UniGraph& G): graph(G) {
		marked.resize(graph.get_V());
		for (int s=0; s < graph.get_V(); ++s) {
			if(!marked[s]) {
				dfs(s, s);
			}
		}
	}

	void dfs(int v, int u) {
		marked[v] = true;

		const std::vector<int>& temp = graph.adj(v);
		for (auto pos=temp.begin(); pos!=temp.end(); ++pos) {
			if(!marked[*pos]) {
				dfs(*pos, v);  // call dfs with *pos's source node v -> will be u
			} else if (*pos != u) {  // if visisted node is not its source node u, then it is a cycle!
				//std::cout << "Cycle Detected: " << v << " " << u << " " << *pos << std::endl;
				hasCycle = true;
			}
		}
	}

	bool has_cycle() {
		return hasCycle;
	}
};

class DirectedCycle {
protected:
	std::vector<bool> marked;
	std::vector<int> edgeTo;
	std::stack<int> cycle;
	std::vector<bool> onStack;

	DiGraph& graph;

public:
	DirectedCycle(DiGraph& G): graph(G) {
		onStack.resize(graph.get_V());
		edgeTo.resize(graph.get_V());
		marked.resize(graph.get_V());
		for (int v=0; v < graph.get_V(); ++v) {
			if(!marked[v]) dfs(v);
		}
	}

	void dfs(int v) {
		onStack[v] = true;
		marked[v] = true;
		const std::vector<int>& temp = graph.adj(v);
		for (auto w = temp.begin(); w != temp.end(); ++w) {
			if(hasCycle()) {
				return;
			} else if (!marked[*w]) {
				edgeTo[*w] = v;
				dfs(*w);
			} else if (onStack[*w]) {  // page 577
				//std::stack<int> cycle;
				for(int x = v; x != *w; x = edgeTo[x]) {
					cycle.push(x);
				}
				cycle.push(*w);
				cycle.push(v);
			}
		}
		onStack[v] = false;
	}

	bool hasCycle() {
		return !cycle.empty();
	}

	std::stack<int> Cycle() {
		return cycle;
	}
};