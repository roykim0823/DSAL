// Chapter 22 driver: maximum flow in a network, plus bipartite matching modeled
// as a max-flow problem.  No arguments required -- both demos are built in.
//
//   ./ch22_network_flow_main

#include <iostream>
#include <utility>
#include <vector>

#include "flow_network.h"

using ch22::FlowNetwork;
using ch22::MaxFlow;

namespace {

// Sedgewick's 6-vertex example network (Chapter 22).  Source = 0, sink = 5.
void MaxFlowDemo() {
  const int kV = 6, kSource = 0, kSink = 5;
  const std::vector<std::vector<int>> kEdges = {  // {v, w, capacity}
      {0, 1, 2}, {0, 2, 3}, {1, 3, 3}, {1, 4, 1},
      {2, 3, 1}, {2, 4, 1}, {3, 5, 2}, {4, 5, 3}};

  FlowNetwork g(kV);
  for (const auto& e : kEdges) g.Insert(e[0], e[1], e[2]);

  MaxFlow mf(g, kSource, kSink);

  std::cout << "=== Maximum flow (6-vertex sample network) ===\n";
  std::cout << "Source = " << kSource << ", sink = " << kSink << "\n";
  std::cout << "Max-flow value: " << mf.value() << "\n";
  std::cout << "Flow on each edge (v -> w : flow/capacity):\n";
  for (int id = 0; id < g.E(); ++id) {
    const ch22::Edge& e = g.edge(id);
    std::cout << "  " << e.v() << " -> " << e.w() << " : " << e.flow() << "/"
              << e.cap() << "\n";
  }
}

// Bipartite matching as max flow: source -> left, left->right edges, right ->
// sink, all with unit capacity.  A saturated left->right edge is a match.
void BipartiteMatchingDemo() {
  const int kLeft = 4, kRight = 4;
  // Preferences: left vertex i may be matched to any right vertex listed.
  const std::vector<std::pair<int, int>> kPrefs = {
      {0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 3}, {3, 2}, {3, 3}};

  // Vertex layout: 0..kLeft-1 = left, kLeft..kLeft+kRight-1 = right,
  // then source and sink.
  const int kSource = kLeft + kRight;
  const int kSink = kLeft + kRight + 1;
  FlowNetwork g(kLeft + kRight + 2);

  for (int i = 0; i < kLeft; ++i) g.Insert(kSource, i, 1);
  for (int j = 0; j < kRight; ++j) g.Insert(kLeft + j, kSink, 1);
  for (const auto& p : kPrefs) g.Insert(p.first, kLeft + p.second, 1);

  MaxFlow mf(g, kSource, kSink);

  std::cout << "\n=== Bipartite matching via max flow ===\n";
  std::cout << "Maximum matching size: " << mf.value() << "\n";
  std::cout << "Matched pairs (left = right):\n";
  for (int id = 0; id < g.E(); ++id) {
    const ch22::Edge& e = g.edge(id);
    if (e.v() < kLeft && e.w() >= kLeft && e.w() < kLeft + kRight &&
        e.flow() == 1) {
      std::cout << "  L" << e.v() << " = R" << (e.w() - kLeft) << "\n";
    }
  }
}

}  // namespace

int main() {
  MaxFlowDemo();
  BipartiteMatchingDemo();
  return 0;
}
