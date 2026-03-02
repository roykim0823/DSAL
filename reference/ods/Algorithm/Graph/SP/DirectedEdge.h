#ifndef _DIRECTED_EDGE
#define _DIRECTED_EDGE

#include <iostream>
#include <string>

class DirectedEdge {
	int v;	// one vertx
	int w;	// the other vertex
	double weight;	// edge weight

public:
	DirectedEdge(int v, int w, double weight)
	{
		this->v = v;
		this->w = w;
		this->weight = weight;
	}

	double get_weight() { return weight; }
	int get_from()	{ return v;	}
	int get_to()	{ return w;	}

	void get_DirectedEdge()
	{
		std:cout << v << "-" << w << " W=" << weight << endl;
	}
}

#endif
