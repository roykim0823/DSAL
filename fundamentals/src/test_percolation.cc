#include "percolation.h"
#include <iostream>

int main() {
    int n = 4; // 4x4 grid
    Percolation p(n);

    // Open some sites to make it percolate
    p.open(0, 0);
    p.open(1, 0);
    p.open(1, 1);
    p.open(2, 1);
    p.open(3, 1);
    p.open(3, 2); 
    p.open(3, 3); // Example path from top to bottom

    std::cout << "Does the system percolate? " << (p.percolates() ? "Yes" : "No") << std::endl;

    return 0;
}