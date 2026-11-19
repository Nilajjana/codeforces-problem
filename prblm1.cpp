#include <bits/stdc++.h>
#include <iostream>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> path;
vector<vector<int>> cycles;
void cyclefdr(int node, int parent) {
  visited[node] = true;
  path.push_back(node);
  for (int neighbour : adj[node]) {
    if (!visited[neighbour])
      cyclefdr(neighbour, node);
    else if (neighbour != parent && visited[neighbour]) {
      vector<int> cycle;
      for (int i = static_cast<int>(path.size()) - 1; i >= 0; i--) {
        cycle.push_back(path[i]);
        if (path[i] == neighbour)
          break;
      }
      cycles.push_back(cycle);
      cycle.clear();
    }
  }
  path.pop_back();
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;
  int m = 0, n = 0;
  int u = 0, v = 0;
  while (t--) {
    cin >> n >> m;
    visited.assign(n, false);
    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
      cin >> u >> v;
      u--;
      v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    cyclefdr(0, -1);
    int i = 0;
    for (const auto &cycle : cycles) {
      cout << "cycle " << i++ << "is \n";
      for (int vertex : cycle) {
        cout << vertex + 1 << "\n";
      }
    }
    path.clear();
    cycles.clear();
  }
  return 0;
}
