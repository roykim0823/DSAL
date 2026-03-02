#include <iostream>
#include "FlowEdge.h"
#include "FlowNetwork.h"
#include "FordFulkerson.h"

using namespace std;
int main()
{
	FlowEdge e1(0, 1, 2.0);
	FlowEdge e2(0, 2, 3.0);
	FlowEdge e3(1, 3, 3.0);
	FlowEdge e4(1, 4, 1.0);
	FlowEdge e5(2, 3, 1.0);
	FlowEdge e6(2, 4, 1.0);
	FlowEdge e7(3, 5, 2.0);
	FlowEdge e8(4, 5, 3.0);

	FlowNetwork net(6);
    ///*
	net.addEdge(e1); 
	net.addEdge(e2); 
	net.addEdge(e3); 
	net.addEdge(e4); 
	net.addEdge(e5); 
	net.addEdge(e6); 
	net.addEdge(e7); 
	net.addEdge(e8); 
	net.print_all();
	//*/
	int s=0, t=net.get_V()-1;
	cout << "Max flow from " << s << " to " << t << endl;
	FordFulkerson maxflow(net, s, t);

	///*
	// compute maximum flow and minimum cut
	cout<< "Compute maximum flow and minimum cut" << endl;
	for(int v=0; v<net.get_V(); v++) {
		vector<FlowEdge>::iterator pos;
		for(pos=net.adj[v].begin(); pos!=net.adj[v].end(); ++pos) {
			if(( v==pos->from()) && pos->get_flow()>0)
			 	pos->print();
		}
		cout << endl;
	}

	// print min-cut
	cout << "Min cut: ";
	for(int v=0; v<net.get_V(); v++) {
		if(maxflow.inCut(v)) cout << v << " ";
	}
	cout << endl;

	cout << "Max flow value = " << maxflow.get_value() << endl;
	net.print();
    //*/
}                

