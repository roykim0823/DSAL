// Chapter 19 driver: digraphs and DAGs.  No arguments required.
//
//   ./ch19_digraphs_dags_main
//
// The demo:
//   1. builds a fixed sample DAG and prints a topological order
//      (both the DFS reverse-postorder and Kahn source-queue versions);
//   2. builds a fixed sample digraph containing cycles and reports the
//      number of strong components and which vertices share one;
//   3. answers a few reachability queries via the transitive closure.

#include <iostream>
#include <vector>

#include "digraph.h"
#include "strong_components.h"
#include "topological_sort.h"
#include "transitive_closure.h"

using ch19::Digraph;
using ch19::Edge;
using ch19::StrongComponents;
using ch19::TopoSortDFS;
using ch19::TopoSortKahn;
using ch19::TransitiveClosure;

namespace {

Digraph BuildDigraph(int V, const std::vector<Edge>& edges) {
  Digraph G(V);
  for (const Edge& e : edges) G.insert(e);
  return G;
}

void PrintAdjacency(const Digraph& G) {
  for (int v = 0; v < G.V(); ++v) {
    std::cout << "  " << v << ":";
    Digraph::adjIterator A(G, v);
    for (int t = A.beg(); !A.end(); t = A.nxt()) std::cout << ' ' << t;
    std::cout << '\n';
  }
}

}  // namespace

int main() {
  // ---- 1. Topological sort of a sample DAG (8 vertices). ----
  // A small task-dependency graph; every edge points "forward".
  Digraph dag = BuildDigraph(8, {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {2, 4},
                                 {3, 5}, {4, 5}, {5, 6}, {6, 7}});

  std::cout << "Sample DAG (" << dag.V() << " vertices, " << dag.E()
            << " edges):\n";
  PrintAdjacency(dag);

  TopoSortDFS<Digraph> ts_dfs(dag);
  std::cout << "\nTopological order (DFS reverse-postorder):";
  for (int i = dag.V() - 1; i >= 0; --i) std::cout << ' ' << ts_dfs.order(i);
  std::cout << '\n';

  TopoSortKahn<Digraph> ts_kahn(dag);
  std::cout << "Topological order (Kahn source-queue):  ";
  for (int i = 0; i < dag.V(); ++i) std::cout << ' ' << ts_kahn.order(i);
  std::cout << (ts_kahn.valid() ? "   [acyclic]\n" : "   [CYCLE!]\n");

  // ---- 2. Strong components of a digraph with cycles (8 vertices). ----
  // Cycles: {0,1,2}, {3,4,5}, {6,7}; vertex link 2->3, 5->6 join them.
  Digraph dg = BuildDigraph(8, {{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}, {4, 5},
                                {5, 3}, {5, 6}, {6, 7}, {7, 6}});

  std::cout << "\nSample digraph with cycles (" << dg.V() << " vertices, "
            << dg.E() << " edges):\n";
  PrintAdjacency(dg);

  StrongComponents<Digraph> sc(dg);
  std::cout << "\nStrong components: " << sc.count() << '\n';
  for (int c = 0; c < sc.count(); ++c) {
    std::cout << "  component " << c << ":";
    for (int v = 0; v < dg.V(); ++v)
      if (sc.id(v) == c) std::cout << ' ' << v;
    std::cout << '\n';
  }

  const int pairs[][2] = {{0, 2}, {0, 7}, {6, 0}, {3, 5}};
  std::cout << "  strongly connected? ";
  for (const auto& p : pairs)
    std::cout << p[0] << (sc.stronglyReachable(p[0], p[1]) ? "~" : "/") << p[1]
              << "  ";
  std::cout << "(~ = same component, / = not)\n";

  // ---- 3. Reachability via transitive closure. ----
  TransitiveClosure<Digraph> tc(dg);
  std::cout << "\nReachability (transitive closure):\n";
  const int queries[][2] = {{0, 7}, {7, 0}, {3, 2}, {2, 6}};
  for (const auto& q : queries)
    std::cout << "  " << q[0] << " -> " << q[1] << " : "
              << (tc.reachable(q[0], q[1]) ? "reachable" : "not reachable")
              << '\n';

  return 0;
}
