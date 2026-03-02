/*
 * Graph.h
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
namespace mySTL {

template<typename T>
class Graph {
protected:
	int n;
	//bool **a;
	std::vector<std::vector<T>> graph;

public:
	Graph(int num): n(num), graph(n) {}
	virtual ~Graph() {}

	virtual void addEdge(int i, int j) 		= 0; 
	virtual void removeEdge(int i, int j) 	= 0;
	virtual bool hasEdge(int i, int j) 		= 0;

	template<typename T2>
	void _outEdges(int i, std::vector<T2> &edges) {
		for (int j = 0; j < n; j++)
			if (hasEdge(i, j)) edges.push_back(j);  	// edge i -> j
	}

	template<typename T2>
	void _inEdges(int i, std::vector<T2> &edges) {
		for (int j = 0; j < n; j++)
			if (hasEdge(j, i)) edges.push_back(j);  	// edge j -> i
	}

	int size() { return n; }
};

template<typename T>
class AdjMatrix_t : Graph<T> {
	using Graph<T>::graph;
	using Graph<T>::n;
public:
	AdjMatrix_t(int num): Graph<T>(num) { 	// call Graph Constructor
		for(int i=0; i<n; i++)
			graph[i].resize(n, false);
	}
    ~AdjMatrix_t() {}
	void addEdge(int i, int j) 		{ graph[i][j] = true; }
	void removeEdge(int i, int j) 	{ graph[i][j] = false; }
	bool hasEdge(int i, int j) 	   	{ return graph[i][j]; }
	int nVertices() {
		return this->size();
	}
	template<typename T2>
	void outEdges(int i, std::vector<T2> &edges) {
		this->_outEdges(i, edges);
	}
	template<typename T2>
	void intEdges(int i, std::vector<T2> &edges) {
		this->_inEdges(i, edges);
	}
};

typedef AdjMatrix_t<bool> AdjMatrix; 	// currently bool is only used

template<typename T>
class AdjList : Graph<T> {
	using Graph<T>::graph;
	using Graph<T>::n;
	//using Graph<T>::nVertices;
protected:
	int search(int i, T j) {
		for(int k=0; k < (int)graph[i].size(); k++) {
			if(graph[i][k]==j)
				return k;
		}
		return -1;
	}

public:
	AdjList(int num): Graph<T>(num) {}
	~AdjList() {}
	void addEdge(int i, T j)  	{ graph[i].push_back(j); }
	void removeEdge(int i, T j) { 
		int idx = search(i, j);
		if(idx != -1) 
			graph[i].erase(graph[i].begin()+idx);
	}
	bool hasEdge(int i, T j) {
		int idx = search(i, j);
		if(idx != -1) 
			return true;
		return false;
	}
	int nVertices() {
		return this->size();
	}
	template<typename T2>
	void outEdges(int i, std::vector<T2> &edges) {
		this->_outEdges(i, edges);
	}
	template<typename T2>
	void intEdges(int i, std::vector<T2> &edges) {
		this->_inEdges(i, edges);
	}
};

} /* namespace mySTL */
#endif /* GRAPH_H_ */
