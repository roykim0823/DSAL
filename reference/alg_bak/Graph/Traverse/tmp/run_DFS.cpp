#include <vector>
#include <iostream>
#include "DepthFristSearch.h"
//using namespace std;

int main() 
{
	int vertices=6;
	int edges[8][2] = { {0,2},  {0, 1}, {1, 2}, {3, 5}, {3, 4}, {2, 3}, {2, 4}, {0, 5}};

	Graph G1(vertices);
	cout << "Graph: V=6, E=8" << endl;
	for(int i=0; i<8; i++)
		G1.addEdge(edges[i][0], edges[i][1]);
	cout << "Num of Vertices: " << G1.get_V() << "\n";
	cout << "Num of Edges: " << G1.get_E() << "\n";
	G1.get_adjList();

	DepthFirstSearch DFS(G1);
	

}


