#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "union_find.h"
using namespace std;

int main(int argc, char *argv[])
{
	// Read Graph file
	// Read airport file and extract edge list
	ifstream ifile(argv[1]);	
    string line;

	// First line is the number of nodes
	getline(ifile, line);
	vector<string> results;
	boost::split(results, line, boost::is_any_of(" "));
	int N = boost::lexical_cast<int>(results[0]);

	QuickFindUF qfUF(N);
	QuickUnionUF quUF(N);
	WeightedQuickUnionUF wquUF(N);

	// Construct EdgeWeightedDigraph from the file
	while(getline(ifile, line)) {
		vector<string> results;
		boost::split(results, line, boost::is_any_of(" "));
		// p, q
		int p = boost::lexical_cast<int>(results[0]); 
		int q = boost::lexical_cast<int>(results[1]); 
		if(qfUF.connected(p, q)==false)		
			qfUF.connect(p, q);
		if(quUF.connected(p, q)==false)
			quUF.connect(p, q);
		if(wquUF.connected(p, q)==false)
			wquUF.connect(p, q);
	}
	ifile.close();
    
    cout << "components" << qfUF.get_count() << endl;
    cout << "components" << quUF.get_count() << endl;
    cout << "components" << wquUF.get_count() << endl;
}
