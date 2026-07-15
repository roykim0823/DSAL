// Chapter 17 driver: build one small undirected graph in both representations
// (adjacency matrix and adjacency list) from a fixed edge list, then exercise
// the representation-independent clients on each.
//
//   ./ch17_graph_properties_main   # no arguments; runs the built-in sample
//
// The two representations are populated from the same edges and produce the
// same edge list and degrees -- demonstrating that client code written against
// the shared ADT interface is oblivious to the underlying storage.

#include <iostream>
#include <vector>

#include "graph.h"
#include "graph_util.h"

using ch17::DEGREE;
using ch17::DenseGRAPH;
using ch17::Edge;
using ch17::edges;
using ch17::show;
using ch17::SparseGRAPH;

namespace {

// Sample undirected graph on 8 vertices (Sedgewick, Chapter 17).
const int kSampleV = 8;
const std::vector<Edge> kSample = {{0, 2}, {0, 5}, {0, 7}, {1, 7}, {2, 6},
                                   {3, 4}, {3, 5}, {4, 5}, {4, 6}, {4, 7}};

template <class Graph>
void Report(const char* label, const Graph& G) {
  std::cout << "== " << label << " (" << G.V() << " vertices, " << G.E()
            << " edges) ==\n";
  std::cout << "adjacency lists:\n";
  show(G);

  std::cout << "degrees:";
  DEGREE<Graph> deg(G);
  for (int v = 0; v < G.V(); v++) std::cout << " " << v << ":" << deg[v];
  std::cout << '\n';

  std::cout << "edges():";
  for (const Edge& e : edges(G)) std::cout << " " << e.v << "-" << e.w;
  std::cout << "\n\n";
}

}  // namespace

int main() {
  DenseGRAPH dense(kSampleV);
  SparseGRAPH sparse(kSampleV);
  for (const Edge& e : kSample) {
    dense.insert(e);
    sparse.insert(e);
  }

  Report("DenseGRAPH (adjacency matrix)", dense);
  Report("SparseGRAPH (adjacency list)", sparse);
  return 0;
}
