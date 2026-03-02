#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "FordFulkerson.h"

using namespace std;
int main(int argc, char *argv[])
{
	// Read file
	if(argc<2)
	{
		cerr << "Specify input file." << endl;
		return 0;
	}
    
	ifstream ifile(argv[1]);
	string line;
	vector<string> tokens;
	
	// Read the number of vertices
	getline(ifile, line);
	boost::split(tokens, line, boost::is_any_of(" "));
	int V = boost::lexical_cast<int>(tokens[0]);
	FlowNetwork G(V);

	// Read the number of edges
	getline(ifile, line);
	boost::split(tokens, line, boost::is_any_of(" "));
	int E = boost::lexical_cast<int>(tokens[0]);
	
	// Read each FlowEdge (Directed edge with capacity)
	for(int i=0; i<E; i++) {
	 	getline(ifile, line);
		vector<string> tokens;
		boost::split(tokens, line, boost::is_any_of(" "));
		int v = boost::lexical_cast<int>(tokens[0]);
		int w = boost::lexical_cast<int>(tokens[1]);
		double cap = boost::lexical_cast<double>(tokens[2]);
        G.addEdge(new FlowEdge(v, w, cap));
	}
    G.print_all();
    G.print();


	int s=0, t=G.get_V()-1;
	cout << "Max flow from " << s << " to " << t << endl;
	FordFulkerson maxflow(G, s, t);

	///*
	// compute maximum flow and minimum cut
	cout<< "Compute maximum flow and minimum cut" << endl;
	G.print();

	cout << "Max flow value = " << maxflow.get_value() << endl;
	// print min-cut
	cout << "Min cut: ";
	for(int v=0; v<G.get_V(); v++) {
		if(maxflow.inCut(v)) cout << v << " ";
	}
	cout << endl;

    //*/
}                

