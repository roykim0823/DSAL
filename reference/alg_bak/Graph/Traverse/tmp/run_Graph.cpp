#include <iostream>
#include "Graph.h"

using namespace std;

int main() 
{
	// graph1: V=13, E=13
	int edges1[13][2] = { {0,5}, {4, 3}, {0, 1}, {9, 12}, {6, 4},
		{5, 4}, {0, 2}, {11, 12}, {9, 10}, {0, 6}, {7, 8}, {9, 11}, 
		{5, 3}};
	Graph G1(13);
	cout << "Graph1: V=13, E=13" << endl;
	for(int i=0; i<13; i++)
		G1.addEdge(edges1[i][0], edges1[i][1]);
	cout << "Num of Vertices: " << G1.get_V() << "\n";
	cout << "Num of Edges: " << G1.get_E() << "\n";
	G1.get_adjList();
	
	/*
	int edges2[11][2] = { {1,2}, {2, 4}, {1, 3}, {2, 3}, {2, 5}, {4, 5},
		{3, 5}, {7, 3}, {8, 3}, {8, 7}, {5, 6}}; 
	Graph G2(8);
	cout << "Graph2: V=8, E=11" << endl;
	for(int i=0; i<11; i++)
		G2.addEdge(edges2[i][0]-1, edges2[i][1]-1);
	cout << "Num of Vertices: " << G2.get_V() << "\n";
	cout << "Num of Edges: " << G2.get_E() << "\n";
	G2.get_adjList();
	*/

}


