#ifndef _EDGE
#define _EDGE

#include <iostream>
#include <string>

class Edge {
	int v;	// one vertx
	int w;	// the other vertex
	double weight;	// edge weight

public:
	Edge(int v, int w, double weight)
	{
		this->v = v;
		this->w = w;
		this->weight = weight;
	}

	double get_weight() { return weight; }
	int get_either()	{ return v;	}
	int other(int vertex)
	{
		if	(vertex == v) return w;
		else if(vertex == w) return v;
		else
		{
			std:cout<< "Error: Inconsistent edgg" << end;
			exit(1);
		}
	}

	int compareTo(Edge that)
	{
		if 		(this.get_weight() < that.get_weight()) return -1;
		else if (this.get_weight() > that.get_weight()) return +1;
		else return 0;
	}

	void get_Edge()
	{
		std:cout << v << "-" << w << " W=" << weight << endl;
	}
};

#endif
