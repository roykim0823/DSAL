#include <vector>
#include <iostream>
#include "ConnectedComponent.h"

int main() {
	// tinyG.txt
	int vertices=13;
	int edges[26][2] = {
		{0, 6}, {0, 2}, {0, 1}, {0, 5}, 
		{1, 0},
		{2, 0},
		{3, 5}, {3, 4},
		{4, 5}, {4, 6}, {4, 3},
		{5, 3}, {5, 4}, {5, 0},
		{6, 0}, {6, 4},
		{7, 8},
		{8, 7},
		{9, 11}, {9, 10}, {9, 12},
		{10, 9}, 
		{11, 9}, {11, 12},
		{12, 11}, {12, 9}
	};


	std::cout << "Graph: V=13, E=26" << std::endl;
	DiGraph G1(vertices);
	for(int i=0; i<26; i++) {
		G1.addEdge(edges[i][0], edges[i][1]);
	}
	std::cout << "Num of Vertices: " << G1.get_V() << "\n";
	std::cout << "Num of Edges: " << G1.get_E() << "\n";
	G1.get_adjList();

	std::cout << "Connected Component:" << std::endl;
	ConnectedComponent<DiGraph> CC(G1);
	std::cout << CC.count() << " components" << std::endl;
	CC.print_connected();

}