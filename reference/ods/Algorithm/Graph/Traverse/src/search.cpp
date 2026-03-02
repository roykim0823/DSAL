#include <vector>
#include <iostream>
#include "Search.h"

int main() {
	// tinyCG.txt
	int vertices=6;
	int edges[8][2] = { {0,5},  {2, 4}, {2, 3}, {1, 2}, {0, 1}, {3, 4}, {3, 5}, {0, 2}};

	UniGraph G1(vertices);
	std::cout << "Graph: V=6, E=8" << std::endl;
	for(int i=0; i<8; i++)
		G1.addEdge(edges[i][0], edges[i][1]);
	std::cout << "Num of Vertices: " << G1.get_V() << "\n";
	std::cout << "Num of Edges: " << G1.get_E() << "\n";
	G1.get_adjList();

	std::cout << "DFS" << std::endl;
	DFS dfs_search(G1);
	dfs_search.print_path();
	std::cout << std::endl;

	std::cout << "DFS iterative" << std::endl;
	DFS dfs_search_iter(G1, 0, true);
	dfs_search_iter.print_path();
	std::cout << std::endl;

	std::cout << "BFS" << std::endl;
	BFS bfs_search(G1);
	bfs_search.print_path();
	std::cout << std::endl;
}