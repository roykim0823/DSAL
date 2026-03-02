#pragma once
#include <queue>
#include <stack>
#include "Cycle.h"
#include "Search.h"

class TopologicalSort {
protected:
	std::stack<int> order_;

public:
	TopologicalSort(DiGraph G) {
		// Topological Sort work only if there is no cycle in directed graph
		if (!DirectedCycle(G).hasCycle()) {
			// NOTE: temporay hard code
			std::vector<int> t;
			DFS dfs(G, t);
			order_ = dfs.get_reversePostorder();
		}
	}

	std::stack<int> order() {
		return order_;
	}

	void print_order() {
		std::stack<int> tmp = order_;
		while(!tmp.empty()) {
			std::cout << tmp.top() << " ";
			tmp.pop();
		}
		std::cout << std::endl;
	}
};