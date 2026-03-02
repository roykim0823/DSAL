#pragma once
#include <vector>
#include <iostream>

class Graph {
protected:
	int V;		// Number of Vertices
	int E;      // Number of Edges
    std::vector<std::vector<int>> adjList;	// Adjacency lists

public:
	Graph(int V) {
		this->V = V;
		this->E = 0;
		adjList.resize(V);
	}

	virtual void addEdge(int v, int w) = 0;  // This is only diff between unidirect and direct graph!

	int get_V() { return V;}
	int get_E() { return E;}

	const std::vector<int>& adj(int v) {return adjList[v];}

	void get_adjList() {
      	for (int i=0; i<V; i++) {
			std::cout << i << ":";
			for(int j=0; j<adjList[i].size(); j++)
				std::cout << " " << adjList[i][j];
			std::cout << "\n";
		}
	}
};

class UniGraph : public Graph {
public:
	UniGraph(int V): Graph(V) {}

	void addEdge(int v, int w) override {
		// Add two Edges in undirected graph
		adjList[v].push_back(w);	// Add w to v's list
		adjList[w].push_back(v); 	// Add v to w's list
		E++;
	}
};


class DiGraph : public Graph {
public:
	DiGraph(int V): Graph(V) {}

	void addEdge(int v, int w) override {
		adjList[v].push_back(w);	// Add v2 to v1's list
		E++;
	}

	DiGraph reverse() {
		DiGraph R(V);
		for (int v=0; v<V; ++v) {
			const std::vector<int>& temp = adjList[v];
			for(auto w = temp.begin(); w != temp.end(); ++w) {
				R.addEdge(*w, v);
			}
		}
		return R;
	}
};
