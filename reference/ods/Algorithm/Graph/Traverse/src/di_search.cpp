#include <vector>
#include <iostream>
#include "Search.h"

int main() {
	// tinyDG.txt
	int vertices=13;
	int edges[22][2] = { {4, 2},  {2, 3}, {3, 2}, {6, 0}, {0, 1}, {2, 0}, {11, 12}, {12, 9},
						 {9, 10},  {9, 11}, {8, 9}, {10, 12}, {11, 4}, {4, 3}, {3, 5}, {7, 8},
						 {8, 7}, {5, 4}, {0, 5}, {6, 4}, {6, 9}, {7, 6}
						};

	DiGraph G1(vertices);
	std::cout << "Graph: V=6, E=8" << std::endl;
	for(int i=0; i<22; i++)
		G1.addEdge(edges[i][0], edges[i][1]);
	std::cout << "Num of Vertices: " << G1.get_V() << "\n";
	std::cout << "Num of Edges: " << G1.get_E() << "\n";
	G1.get_adjList();

	std::cout << "DFS" << std::endl;
	DFS dfs_search(G1, 1);
	dfs_search.print_reachable();

	DFS dfs_search2(G1, 2);
	dfs_search2.print_reachable();

	DFS dfs_search3(G1, {1, 2, 6});
	dfs_search3.print_reachable();
}