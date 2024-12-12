// Kosaraju {{{
struct Kosaraju {
  int N;
  stack<int> S;
  vector<int> comp;
  vector<bool> vis;
  vector<vector<int>> G, RG;

  Kosaraju(vector<vector<int>> const& G) 
  : N(size(G)), G(G), RG(N), vis(N), comp(N, -1) {
    for (int i = 0; i < N; i++) {
      for (auto j : G[i]) {
        RG[j].emplace_back(i);
      }
    }
    
    for (int i = 0; i < N; i++) {
      if (!vis[i]) {
        dfs(i);
      }
    }

    fill(begin(vis), end(vis), 0);

    int num = 0;
    while (!empty(S)) {
      int u = S.top();
      S.pop();
      
      if (!vis[u]) {
        scc(u, num++);
      }
    }
  }

  void dfs(int v) {
    vis[v] = 1;
    for (auto u : G[v]) {
      if (!vis[u]) {
        dfs(u);
      }
    }
    S.emplace(v);
  }

  void scc(int v, int c) {
    vis[v] = 1, comp[v] = c;
    for (auto u : RG[v]) {
      if (!vis[u]) {
        scc(u, c);
      }
    }
  }
};
//}}}

// TwoSat {{{
struct TwoSat {
  int N;
  vector<vector<int>> G;
  TwoSat(int N) : N(N), G(2*N) {}

  int neg(int u) { return u + ((u < N) ? N : -N); }

  void add_or(int u, int v) {
    G[neg(u)].emplace_back(v);
    G[neg(v)].emplace_back(u);
  }

  pair<bool, vector<bool>> solve() {
    vector<bool> sol(N);
    auto scc = Kosaraju(G).comp;
    for (int i = 0; i < N; i++) {
      if (scc[i] == scc[neg(i)]) return {0, {}};
      sol[i] = (scc[i] > scc[neg(i)]);
    }
    return {1, sol};
  }
};
//}}}
