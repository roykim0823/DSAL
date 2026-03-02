#include <vector>
#include <iostream>
#include "Search.h"
#include "TopologicalSort.h"

template <typename T>
void print_order(T& order) {
	while(!order.empty()) {
		std::cout << order.front() << " ";
		order.pop();
	}
	std::cout << std::endl;
}

int main() {
	// page 575, DAG graph
	int vertices=13;
	int edges[15][2] = { {0, 5}, {0, 1}, {0, 6},  // reorder to match the page 579 result
						 {2, 0}, {2, 3},
						 {3, 5},
						 {5, 4},
						 {6, 4}, {6, 9},
						 {7, 6},
						 {8, 6},
						 {9, 11}, {9, 12}, {9, 10}, // reorder to match the page 579 result
						 {11, 12}
						};

	DiGraph G1(vertices);
	std::cout << "Graph: V=13, E=15" << std::endl;
	for(int i=0; i<15; i++)
		G1.addEdge(edges[i][0], edges[i][1]);
	std::cout << "Num of Vertices: " << G1.get_V() << "\n";
	std::cout << "Num of Edges: " << G1.get_E() << "\n";
	G1.get_adjList();


	std::vector<int> t;

	DFS dfs_search(G1, t);
	std::cout << "Print Travese Order: " << std::endl;
	auto pre = dfs_search.get_preorder();
	auto post = dfs_search.get_postorder();
	auto reversePost = dfs_search.get_reversePostorder();
	print_order(pre);
	print_order(post);
	while(!reversePost.empty()) {
		std::cout << reversePost.top() << " ";
		reversePost.pop();
	}
	std::cout << std::endl;

	TopologicalSort tp_sort(G1);
	tp_sort.print_order();
}