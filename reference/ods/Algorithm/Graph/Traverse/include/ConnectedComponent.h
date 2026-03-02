#pragma once
#include <queue>
#include <stack>
#include "Graph.h"

template <typename T>  // T is UniGraph or DiGraph
class ConnectedComponent {
protected:
	std::vector<bool> marked;	// visited
	std::vector<int> id;     	// component id for each vertex
	int cnt = 0;           	// component count
	T& graph;

public:
	ConnectedComponent(T& G): graph(G) {
		marked.resize(graph.get_V());
		id.resize(graph.get_V());

		for (int s=0; s < graph.get_V(); ++s) {
			if(!marked[s]) {
				dfs(s);
				++cnt;
			}
		}
	}

	void dfs(int v) {
		marked[v] = true;
		id[v] = cnt;
		const std::vector<int>& temp = graph.adj(v);
		for (auto pos=temp.begin(); pos!=temp.end(); ++pos) {
			if(!marked[*pos]) {
				dfs(*pos);
			}
		}
	}

	bool connected(int v, int w) {
		return id[v] == id[w];
	}

	int count() {
		return cnt;
	}

	void print_connected() {
		std::vector<std::vector<int>> component;
		component.resize(cnt);
		for (int i=0; i<graph.get_V(); ++i) {
			component[id[i]].push_back(i);
		}
		for(int i=0; i<cnt; ++i) {
			for(int j=0; j<component[i].size(); ++j) {
				std::cout << component[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};