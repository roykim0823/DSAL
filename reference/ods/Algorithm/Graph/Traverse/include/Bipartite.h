#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include "Graph.h"

template <typename T>  // T is UniGraph or DiGraph
class Bipartite {
protected:
	std::vector<bool> marked;	// visited
	std::vector<bool> color;
	bool isTwoColorable = true;
	T& graph;

public:
	Bipartite(T& G): graph(G) {
		marked.resize(graph.get_V());
		color.resize(graph.get_V());
		for (int s=0; s < graph.get_V(); ++s) {
			if(!marked[s]) {
				dfs(s, s);
			}
		}
	}

	void dfs(int v) {
		marked[v] = true;

		const std::vector<int>& temp = graph.adj(v);
		for (auto pos=temp.begin(); pos!=temp.end(); ++pos) {
			if(!marked[*pos]) {
				color[*pos] =!color[v];
				dfs(*pos);
			} else if (color[*pos] == color[v]) {
				//std::cout << "Tow Color is same: " << *pos << " " << v << std::endl;
				isTwoColorable = false;
			}
		}
	}

	bool isBipartite() {
		return isTwoColorable;
	}
};