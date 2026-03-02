#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> // Added for string parsing
#include <stack>

#include "union_find.h"

using namespace std;

// Helper function to print a vector
void print_vec(const vector<int>& vec) {
    for (int val : vec) 
        cout << val << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        return 1;
    }

    // Read Graph file
    ifstream ifile(argv[1]);
    if (!ifile.is_open()) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    string line;

    // First line is the number of nodes
    int N = 0;
    if (getline(ifile, line)) {
        stringstream ss(line);
        if (!(ss >> N)) {
            cerr << "Error: Invalid format for number of nodes." << endl;
            return 1;
        }
    }

    // Initialize Union-Find objects
    QuickFind qf(N);
    QuickUnion qu(N);
    WeightedQuickUnion wqu(N);
    WQUPC wqupc(N);

    // Read edges from the file
    while (getline(ifile, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        stringstream ss(line);
        int p, q;
        
        // Extract two integers from the line
        if (ss >> p >> q) {
					if (N<1000) {  // skip union for large graphs to save time
            qf.connect(p, q);
            qu.connect(p, q);
					}
          wqu.connect(p, q);
          wqupc.connect(p, q);
        }
    }
    ifile.close();

    // Output Results
		if (N < 1000) {
    	cout << "QuickFind components: " << qf.count() << endl;
    	cout << "QuickUnion components: " << qu.count() << endl;
		}
    cout << "WeightedQuickUnion components: " << wqu.count() << endl;
    cout << "WQUPC components: " << wqupc.count() << endl;

    return 0;
}