#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "DijkstraSP.h"
using namespace std;

/*
bool comp(pair<int, int>a, pair<int, int>b)
{
 	return a.second > b.second;
}

pair<vector<int>,int> max_path(Graph &G, BFS &bfs, int source)
{

	int maxPathLength=0;
	vector<int> maxPath;
	for (int v=1; v< G.get_V(); v++)
	{
		int pathLength=0;
		vector<int> path_node;
		//cout << source << " to " << v << ":";
		if(bfs.hasPathTo(v))
		{
			stack<int> path = bfs.pathTo(v);
			while(!path.empty())
			{
				int node = path.top();
				if(node==source) path_node.push_back(node);
				else	{
					//cout << "-" << node;
					path_node.push_back(node);
					pathLength++;
				}
				path.pop();
			}
			//cout << " L: " <<pathLength<< endl;
			if(pathLength>maxPathLength)
			{
				maxPathLength=pathLength;
				maxPath=path_node;
			}
		} else
		  ;  //cout << endl;
	}
	return make_pair(maxPath,maxPathLength);

}

void print_diameter(Graph &G, BFS &bfs, int source, int diameter, map<int, string> &invertedIndex, vector<int> &distance)
{

	int maxPathLength=0;
	vector<int> maxPath;
	for (int v=1; v< G.get_V(); v++)
	{
		int pathLength=0;
		vector<int> path_node;
		//cout << source << " to " << v << ":";
		if(bfs.hasPathTo(v))
		{
			stack<int> path = bfs.pathTo(v);
			while(!path.empty())
			{
				int node = path.top();
				if(node==source) path_node.push_back(node);
				else	{
					//cout << "-" << node;
					path_node.push_back(node);
					pathLength++;
				}
				path.pop();
			}
			//cout << " L: " <<pathLength<< endl;
			if(pathLength==diameter)
			//if(pathLength>0)
			{
				maxPathLength=pathLength;
				maxPath=path_node;
				vector<int>::iterator pos;
				for(pos=path_node.begin(); pos != path_node.end(); ++pos)
					cout << setw(3) << *pos << " ";
				cout << " => ";
				for(pos=path_node.begin(); pos != path_node.end(); ++pos)
					cout << invertedIndex[*pos] << " ";
				cout << endl;
				
			}
			// Collect distance distribution
			distance[pathLength]++;
		} else
		  ;  //cout << endl;
	}
}

*/
int main(int argc, char *argv[])
{
	// Read Graph file
	// Read airport file and extract edge list
	ifstream ifile(argv[1]);	
    string line;

	// First line is the number of nodes
	getline(ifile, line);
	vector<string> results;
	boost::split(results, line, boost::is_any_of(","));
	int N = boost::lexical_cast<int>(results[0]);

	EdgeWeightedDiGraph G(N);

	// Construct EdgeWeightedDigraph from the file
	while(getline(ifile, line)) {
		vector<string> results;
		boost::split(results, line, boost::is_any_of(","));
		// v, w, weight
		int v = boost::lexical_cast<int>(results[0]); 
		int w = boost::lexical_cast<int>(results[1]); 
		double weight = boost::lexical_cast<double>(results[2]); 
		DirectedEdge edge(v, w, weight);
        G.addEdge(edge);
	}
	ifile.close();
    
    cout << "Graph Info" << endl;
	cout << "Nodes= " << G.get_V() << ", Edges= " << G.get_E() << endl;
	G.print_graph();
    
	DijkstraSP sp(G, 0);
	
	cout << "A shortest path from 0" << endl;

	for(int i=0; i<G.get_V(); i++)
	if(sp.hasPathTo(i))
	{
		cout << i <<": ";
		stack<DirectedEdge> path = sp.pathTo(i);
		while(!path.empty())
		{
			DirectedEdge node = path.top();
			if(node.get_from()==0) cout <<  node.get_from() << "->" << node.get_to();
			else	{
				cout << "->" << node.get_to(); 
			}
			//cout << node.get_to();
			path.pop();
		}
		cout<<endl;
	}
}
