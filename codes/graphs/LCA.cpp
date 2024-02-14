// (0.1v - fucked up, fix it latter)
struct LCA {/*{{{*/
  int N, TIMER = 0;
  vector<vector<int>> G;
  vector<vector<int>> up;
  vector<int> pre, pos, depth;
  
  const int LOG = 30;

  void dfs(int v, int p) {
    pre[v] = TIMER++, up[v][0] = p;
    for(int i = 1; i < LOG; i++) {
      up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for(auto i : G[v]) {
      if(i == p) continue;
      depth[i] = depth[v] + 1;
      dfs(i, v);
    }
    pos[v] = TIMER;
  }
 
  bool is_ancestor(int u, int v) {
    return (pre[u] <= pre[v] && pos[u] >= pos[v]);
  }
 
  int lca(int u, int v) {
    if(is_ancestor(u, v)) return u;
    if(is_ancestor(v, u)) return v;
 
    for(int i = LOG - 1; i >= 0; i--) {
      if(!is_ancestor(up[u][i], v)) {
        u = up[u][i];
      }
    }
    return up[u][0];
  }
 
  explicit LCA(vector<vector<int>> const& G) 
    : G(G), N(size(G)), pre(N, -1), pos(N, -1), depth(N, 0), up(N, vector<int>(LOG, 0)) {

    for(int i = 0; i < N; i++) {
      if(pre[i] == -1) {
        dfs(i, i);
      }
    }
  }
};/*}}}*/
