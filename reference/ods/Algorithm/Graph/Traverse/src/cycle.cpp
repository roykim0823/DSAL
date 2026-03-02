#include <vector>
#include <iostream>
#include "Cycle.h"

int main() {
	// tinyCG.txt
	int vertices=6;
	const int Edges=8;
	int edges[Edges][2] = { {0,5},  {2, 4}, {2, 3}, {1, 2}, {0, 1}, {3, 4}, {3, 5}, {0, 2}}; // three cycles
	//int edges[Edges][2] = {           {2, 4}, {2, 3},         {0, 1},           {3, 5}, {0, 2}};  // no cycle

	UniGraph G1(vertices);
	std::cout << "Graph: V=7, E=8" << std::endl;
	for(int i=0; i<Edges; i++)
		G1.addEdge(edges[i][0], edges[i][1]);
	std::cout << "Num of Vertices: " << G1.get_V() << "\n";
	std::cout << "Num of Edges: " << G1.get_E() << "\n";
	G1.get_adjList();

	std::cout << "Cycle in Undirected Graph" << std::endl;
	Cycle cycle(G1);
	std::cout << cycle.has_cycle() << std::endl;
}