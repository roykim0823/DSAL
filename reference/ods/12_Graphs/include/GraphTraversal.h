/*
 * Algorithms.h
 *
 *  Created on: 2011-11-30
 *      Author: morin
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>

namespace mySTL {

// Breadth-First Search
template<typename Graph>
void bfs(Graph &g, int startingNode) {
	std::vector<bool> visited(g.nVertices(), false);	// auxiliary boolean array to check visted nodes
	std::queue<int> q;		// queue: keep the visiting node
	q.push(startingNode);		  	// push back, Add starting node
	visited[startingNode] = true;
	//cout << "bfs " << startingNode << " visited " << endl;
	while (q.size() > 0) {
		int i = q.front();
		q.pop(); 	// pop front
		std::vector<int> edges;		// stack to store i's outgoing Edges
		g.outEdges(i, edges);		// put i's outgoing Edges to edges
		for (size_t k = 0; k < edges.size(); k++) {
			size_t j = edges[k]; 			// Get dest's node
			if (!visited[j]) {
				q.push(j); 	// push back
				visited[j] = true;
				//cout << "bfs " << j << " visited " << endl;
			}
		}
	}
}

// dfs vertex status
enum node { white, grey, black };	// white: never seen the vertex
		  							// grey: currently visting node
		  							// black: visted node (done)

// Depth-First Search: Recursive
template<class Graph>
void dfs(Graph &g, int startingNode, std::vector<bool>  &visited) {
	visited[startingNode] = true;  	 	// currently visiting i
	//cout << "dfs " << startingNode << " visited " << endl;

	std::vector<int> edges; 	// stack to store i's outgoing Edges
	g.outEdges(startingNode, edges);   	// put i's outgoing Edges to edges
	for (size_t k = 0; k < edges.size(); k++) {
		size_t j = edges[k];	// get dest's node
		if (visited[j] == false)
			dfs(g, j, visited);
	}
}

template<class Graph>
void dfs(Graph &g, int startingNode) {
	std::vector<bool> visited(g.nVertices(), false);
	dfs(g, startingNode, visited);
}

// DFS -> Iterative Version
template<class Graph>	// Iterative Version
void dfs2(Graph &g, int startingNode) {
	std::vector<bool> visited(g.nVertices(), false);	// auxiliary boolean array to check visted nodes
	std::queue<int> q;		// queue: keep the visiting node
	q.push(startingNode);		  	// push back, Add starting node
	while (q.size() > 0) {
		int i = q.front();
		q.pop();    	// pop front
		if (visited[i] == false) {
			visited[i] = true;
			//cout << "dfs2 " << i << " visited " << endl;
			std::vector<int> edges;
			g.outEdges(i, edges);	// get dest's node
			for (size_t k = 0; k < edges.size(); k++)
				q.push(edges[k]);	// push neighbors node
		}
	}
}

} /* namespace ods */

#endif /* GRAPH_H */
