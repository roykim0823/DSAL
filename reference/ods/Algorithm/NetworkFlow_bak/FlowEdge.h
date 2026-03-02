#ifndef _FLOW_EDGE
#define _FLOW_EDGE

#include <iostream>
#include <string>

class FlowEdge {
	int v;	// from
	int w;	// to
	double capacity;	
	double flow;

public:
	FlowEdge(int v=0, int w=0, double capacity=0.0, double flow=0.0)
	{
		if(capacity < 0) {
			std::cerr << "Negative edge capacity" << std::endl;
		}

		this->v = v;
		this->w = w;
		this->capacity = capacity;
		this->flow = flow;
	}

	// Copy Constructor
	FlowEdge(const FlowEdge &e) {
		this->v = e.v;
		this->w = e.w;
		this->capacity = e.capacity;
		this->flow = e.flow;
	}

	int from() 	{ return v; 	}
	int to()	{ return w; 	}
	double get_capacity() { return capacity; }
	double get_flow() { return flow; }

	int other(int vertex) {
		if (vertex == v) return w;
		else if (vertex == w) return v;
		else {
			std::cerr << "Illegal endpoint" << std::endl;
		}
	}
			
	int residualCapacityTo(int vertex) {
		if (vertex == v) return flow;
		else if (vertex == w) return capacity - flow;
		else {
			std::cerr << "Illegal endpoint" << std::endl;
		}
	}

	void addResidualFlowTo(int vertex, double delta) {
		if (vertex == v) flow -= delta;
		else if (vertex == w) flow += delta;
		else {
			std::cerr << "Illegal endpoint" << std::endl;
		}
	}

	void print() {
		std::cout << v << "->" << w << " " << flow << "/" << capacity << ", ";
	}
};

#endif
		



			
	


