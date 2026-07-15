#ifndef ALG_REF_CH22_FLOW_NETWORK_H_
#define ALG_REF_CH22_FLOW_NETWORK_H_

// Chapter 22: Network Flow -- a flow network with residual-capacity edges and a
// maximum-flow solver based on augmenting paths.
//
// Modernized from Sedgewick, "Algorithms in C++, 3rd Ed.", Chapter 22.  The
// original used a templated adjacency-list GRAPH with raw Edge* pointers; here
// the network owns its edges in a std::vector and exposes an adjacency list of
// edge indices, so both endpoints of an edge share the same flow state.
//
// Edge (Sedgewick's EDGE): a directed edge v->w with a capacity and a flow.
//   from(x)        -- is x the tail (v) of this edge?
//   other(x)       -- the endpoint that is not x.
//   CapResidualTo(x) -- residual capacity in the direction toward x.
//   AddFlowTo(x, d)  -- push d units of flow toward x (undoes flow if x == v).
//
// MaxFlow: shortest-augmenting-path (Edmonds-Karp / BFS) maximum flow.
//   Complexity: O(V * E^2) with BFS-chosen augmenting paths.

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace ch22 {

// A directed edge carrying flow, viewable from either endpoint.
class Edge {
 public:
  Edge(int v, int w, int cap) : v_(v), w_(w), cap_(cap), flow_(0) {}

  int v() const { return v_; }        // tail
  int w() const { return w_; }        // head
  int cap() const { return cap_; }    // capacity
  int flow() const { return flow_; }  // current flow

  bool from(int x) const { return v_ == x; }
  int other(int x) const { return from(x) ? w_ : v_; }

  // Residual capacity in the direction pointing at x.
  int CapResidualTo(int x) const { return from(x) ? flow_ : cap_ - flow_; }

  // Add d units of flow in the direction pointing at x.
  void AddFlowTo(int x, int d) { flow_ += from(x) ? -d : d; }

 private:
  int v_, w_, cap_, flow_;
};

// Flow network: fixed vertex count, edges stored once and shared between the
// adjacency lists of both endpoints (so residual updates are consistent).
class FlowNetwork {
 public:
  explicit FlowNetwork(int v) : v_(v), adj_(v) {}

  int V() const { return v_; }
  int E() const { return static_cast<int>(edges_.size()); }

  // Insert a directed edge v->w with the given capacity.
  void Insert(int v, int w, int cap) {
    int id = static_cast<int>(edges_.size());
    edges_.emplace_back(v, w, cap);
    adj_[v].push_back(id);
    adj_[w].push_back(id);
  }

  const std::vector<int>& adj(int v) const { return adj_[v]; }
  Edge& edge(int id) { return edges_[id]; }
  const Edge& edge(int id) const { return edges_[id]; }

 private:
  int v_;
  std::vector<Edge> edges_;
  std::vector<std::vector<int>> adj_;
};

// Maximum flow from s to t via shortest augmenting paths (BFS).
class MaxFlow {
 public:
  MaxFlow(FlowNetwork& g, int s, int t) : g_(g), s_(s), t_(t), value_(0) {
    std::vector<int> parent_edge(g.V());
    while (BuildAugmentingPath(parent_edge)) Augment(parent_edge);
  }

  int value() const { return value_; }

 private:
  // BFS over residual edges; parent_edge[x] = edge id used to reach x.
  bool BuildAugmentingPath(std::vector<int>& parent_edge) {
    std::vector<bool> visited(g_.V(), false);
    std::fill(parent_edge.begin(), parent_edge.end(), -1);
    std::queue<int> q;
    q.push(s_);
    visited[s_] = true;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : g_.adj(v)) {
        int w = g_.edge(id).other(v);
        if (!visited[w] && g_.edge(id).CapResidualTo(w) > 0) {
          visited[w] = true;
          parent_edge[w] = id;
          q.push(w);
        }
      }
    }
    return visited[t_];
  }

  // Push the bottleneck residual capacity along the found path.
  void Augment(const std::vector<int>& parent_edge) {
    int d = std::numeric_limits<int>::max();
    for (int v = t_; v != s_;) {
      const Edge& e = g_.edge(parent_edge[v]);
      d = std::min(d, e.CapResidualTo(v));
      v = e.other(v);
    }
    for (int v = t_; v != s_;) {
      Edge& e = g_.edge(parent_edge[v]);
      e.AddFlowTo(v, d);
      v = e.other(v);
    }
    value_ += d;
  }

  FlowNetwork& g_;
  int s_, t_, value_;
};

}  // namespace ch22

#endif  // ALG_REF_CH22_FLOW_NETWORK_H_
