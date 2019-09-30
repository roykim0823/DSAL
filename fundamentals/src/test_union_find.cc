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

void print_vec(vector<int> vec) {
  for (auto pos = vec.begin(); pos != vec.end(); ++pos) 
    cout << *pos << " ";
  cout << endl;
}

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

	QuickFind qf(N);
	QuickUnion qu(N);
	WeightedQuickUnion wqu(N);
	WQUPC wqupc(N);

	// Construct EdgeWeightedDigraph from the file
	while(getline(ifile, line)) {
		vector<string> results;
		boost::split(results, line, boost::is_any_of(" "));
		// p, q
		int p = boost::lexical_cast<int>(results[0]); 
		int q = boost::lexical_cast<int>(results[1]); 
		qf.connect(p, q);
		qu.connect(p, q);
		wqu.connect(p, q);
		wqupc.connect(p, q);
	}
	ifile.close();
    vector<int> id;
    cout << "QuickFind components: " << qf.count() << endl;
    // id = qf.get_id();
    // print_vec(id);

    cout << "QuickUnion components: " << qu.count() << endl;
    cout << "WeightedQuickUnion components: " << wqu.count() << endl;
    cout << "WQUPC components: " << wqupc.count() << endl;
}
