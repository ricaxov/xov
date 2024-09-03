struct LCA {/*{{{*/
  int N, timer = 0;
  vector<vector<int>> G, par;
  vector<int> pre, pos, depth;

  const int LOG = 30;

  void dfs(int v, int p) {
    pre[v] = timer++, par[v][0] = p;
    for (int i = 1; i < LOG; i++) {
      par[v][i] = par[par[v][i-1]][i-1];
    }
    for (auto i : G[v]) {
      if (i == p) continue;
      depth[i] = depth[v]+1;
      dfs(i, v);
    }
    pos[v] = timer;
  }
 
  bool is_ancestor(int u, int v) {
    return (pre[u] <= pre[v] && pos[u] >= pos[v]);
  }
 
  int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
 
    for (int i = LOG-1; i >= 0; i--) {
      if (!is_ancestor(par[u][i], v)) {
        u = par[u][i];
      }
    }
    return par[u][0];
  }
 
  explicit LCA(vector<vector<int>> const& G) : G(G), N(size(G)) {
    depth.assign(N, 0);
    par.assign(N, vector<int>(LOG, -1));
    pre.assign(N, -1), pos.assign(N, -1);
    for (int i = 0; i < N; i++) {
      if (pre[i] == -1) {
        dfs(i, i);
      }
    }
  }
};/*}}}*/
