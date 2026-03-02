#include <vector>
#include <iostream>
#include "DFS.h"

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
	int s=0;

	cout << "A path from node 0" << endl;
	for (int v=0; v< G1.get_V(); v++)
	{
		cout << s << " to " << v << ":";
		if(DFS.hasPathTo(v))
		{
			stack<int> path = DFS.pathTo(v);
			while(!path.empty())
			{
				int node = path.top();
				if(node==s) cout << node;
				else	cout << "-" << node;
				path.pop();
			}
			cout << endl;
		}
	}
}
