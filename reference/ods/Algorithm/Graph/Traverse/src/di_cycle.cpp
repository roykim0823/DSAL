#include <vector>
#include <iostream>
#include "Cycle.h"

int main() {
	// tinyDG.txt
	int vertices=13;
	int edges[22][2] = { {4, 2},  {2, 3}, {3, 2}, {6, 0}, {0, 1}, {2, 0}, {11, 12}, {12, 9},
						 {9, 10},  {9, 11}, {8, 9}, {10, 12}, {11, 4}, {4, 3}, {3, 5}, {7, 8},
						 {8, 7}, {5, 4}, {0, 5}, {6, 4}, {6, 9}, {7, 6}
						};


	DiGraph G1(vertices);
	std::cout << "Graph: V=7, E=8" << std::endl;
	for(int i=0; i<22; i++)
		G1.addEdge(edges[i][0], edges[i][1]);
	std::cout << "Num of Vertices: " << G1.get_V() << "\n";
	std::cout << "Num of Edges: " << G1.get_E() << "\n";
	G1.get_adjList();

	std::cout << "Cycle in Directed Graph" << std::endl;
	DirectedCycle cycle(G1);
	std::cout << cycle.hasCycle() << std::endl;
	std::stack<int> detected_cycle = cycle.Cycle();
	while(!detected_cycle.empty()) {
		std::cout << detected_cycle.top() << " ";
		detected_cycle.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;

	// part of tinyDG
	int vertices2=6;
	int edges2[4][2] = { {0, 5}, {3, 5}, {4, 3}, {5, 4} };
	DiGraph G2(vertices2);
	for(int i=0; i<4; ++i) {
		G2.addEdge(edges2[i][0], edges2[i][1]);
	}
	std::cout << "Cycle in Directed Graph2" << std::endl;
	DirectedCycle cycle2(G2);
	std::cout << cycle2.hasCycle() << std::endl;
	detected_cycle = cycle2.Cycle();
	while(!detected_cycle.empty()) {
		std::cout << detected_cycle.top() << " ";
		detected_cycle.pop();
	}
	std::cout << std::endl;

}