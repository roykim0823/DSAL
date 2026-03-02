#include "union_find.h"
#include <vector>

class Percolation {
private:
    int n_;
    std::vector<bool> open_sites_;
    WQUPC uf_;
    int top_site_;
    int bottom_site_;

    // Helper to convert 2D coordinates to 1D index
    int get_index(int row, int col) {
        return row * n_ + col;
    }

public:
    // Constructor for an n-by-n grid
    Percolation(int n) : n_(n), uf_(n * n + 2) { // +2 for virtual top and bottom
        open_sites_.resize(n * n, false);
        top_site_ = n * n;
        bottom_site_ = n * n + 1;
    }

    // Opens the site (row, col) if it is not already open
    void open(int row, int col) {
        int index = get_index(row, col);
        if (open_sites_[index]) return;
        open_sites_[index] = true;

        // Connect to virtual top if in the first row
        if (row == 0) uf_.connect(index, top_site_);
        // Connect to virtual bottom if in the last row
        if (row == n_ - 1) uf_.connect(index, bottom_site_);

        // Connect to open neighbors (up, down, left, right)
        // Check bounds and if neighbor is open
        int neighbors[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; ++i) {
            int r = row + neighbors[i][0];
            int c = col + neighbors[i][1];
            if (r >= 0 && r < n_ && c >= 0 && c < n_) {
                int neighbor_index = get_index(r, c);
                if (open_sites_[neighbor_index]) {
                    uf_.connect(index, neighbor_index);
                }
            }
        }
    }

    // Checks if the system percolates
    bool percolates() {
        return uf_.find(top_site_) == uf_.find(bottom_site_);
    }
};