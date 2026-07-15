// Chapter 18 driver: build a fixed sample graph and run the graph-search
// algorithms on it -- no arguments required.
//
//   ./ch18_graph_search_main
//
// It prints, for the sample graph:
//   * the adjacency lists
//   * depth-first preorder numbers and reachable count from vertex 0
//   * the number of connected components
//   * whether the graph is bipartite (two-colourable)
//   * breadth-first visit order from a source vertex

#include <iostream>
#include <vector>

#include "graph.h"
#include "graph_search.h"

using ch18::BFS;
using ch18::BI;
using ch18::CC;
using ch18::DFS;
using ch18::Edge;
using ch18::Graph;

namespace {

// Sample undirected graph with 8 vertices and two connected components.
// Component {0,1,2,3,4} contains the triangle 2-3-4 (an odd cycle, so the
// graph is not bipartite); component {5,6,7} is a simple path.
const int kSampleV = 8;
const std::vector<Edge> kSample = {{0, 1}, {0, 2}, {1, 3}, {2, 3},
                                   {3, 4}, {2, 4}, {5, 6}, {6, 7}};

// Prints "v: neighbours" for every vertex using the adjIterator.
void ShowGraph(const Graph& G) {
  for (int v = 0; v < G.V(); ++v) {
    std::cout << "  " << v << ":";
    Graph::adjIterator A(G, v);
    for (int t = A.beg(); !A.end(); t = A.nxt()) std::cout << ' ' << t;
    std::cout << '\n';
  }
}

}  // namespace

int main() {
  Graph G(kSampleV);
  for (const Edge& e : kSample) G.insert(e);

  std::cout << "Sample graph: " << G.V() << " vertices, " << G.E()
            << " edges\n";
  ShowGraph(G);

  DFS<Graph> dfs(G, 0);
  std::cout << "\nDFS preorder from vertex 0 (reached " << dfs.count()
            << " vertices):\n ";
  for (int v = 0; v < G.V(); ++v) std::cout << ' ' << v << ":" << dfs[v];
  std::cout << '\n';

  CC<Graph> cc(G);
  std::cout << "\nConnected components: " << cc.count() << '\n';
  for (int v = 0; v < G.V(); ++v)
    std::cout << "  vertex " << v << " -> component " << cc.id(v) << '\n';

  BI<Graph> bi(G);
  std::cout << "\nBipartite: " << (bi.bipartite() ? "yes" : "no") << '\n';

  const int kSource = 0;
  BFS<Graph> bfs(G, kSource);
  std::cout << "\nBFS visit order from vertex " << kSource << ":\n ";
  for (int v = 0; v < G.V(); ++v) std::cout << ' ' << v << ":" << bfs[v];
  std::cout << '\n';

  return 0;
}
