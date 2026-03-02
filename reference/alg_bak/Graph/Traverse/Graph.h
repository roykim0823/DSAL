#include <vector>
#include <iostream>

using namespace std;

class Graph 
{
	int V;		// Number of Vertices
	int E;      // Number of Edges
    vector<vector<int> > adjList;	// Adjacency lists
public:
	Graph(int V)
	{
		this->V = V;
		this->E = 0;
		adjList.resize(V);
	}
	void addEdge(int v1, int v2)
	{
		// Add two Edges in undirected graph
		adjList[v1].push_back(v2);	// Add v2 to v1's list
		adjList[v2].push_back(v1); 	// Add v1 to v2's list
		E++;
	}
	int get_V() { return V;}
	int get_E() { return E;}
	vector<int> adj(int v) {return adjList[v];}
	void get_adjList()
	{
      	for(int i=0; i<V; i++)
		{
			cout << i << ":";
			for(int j=0; j<adjList[i].size(); j++)
				cout << " " << adjList[i][j];
			cout << "\n";
		}
	}
};

class DiGraph 
{
	int V;		// Number of Vertices
	int E;      // Number of Edges
    vector<vector<int> > adjList;	// Adjacency lists
public:
	DiGraph(int V)
	{
		this->V = V;
		this->E = 0;
		adjList.resize(V);
	}
	void addEdge(int v1, int v2)
	{
		adjList[v1].push_back(v2);	// Add v2 to v1's list
		//adjList[v2].push_back(v1); 	// Add v1 to v2's list
		E++;
	}
	int get_V() { return V;}
	int get_E() { return E;}
	vector<int> adj(int v) {return adjList[v];}
	void get_adjList()
	{
      	for(int i=0; i<V; i++)
		{
			cout << i << ":";
			for(int j=0; j<adjList[i].size(); j++)
				cout << " " << adjList[i][j];
			cout << "\n";
		}
	}
};
