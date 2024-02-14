// (not tested enough)
struct Kosaraju {/*{{{*/
  int N;
  stack<int> S;
  vector<int> C;
  vector<bool> used;
  vector<vector<int>> G, RG;

  Kosaraju(vector<vector<int>> const& G) : N(size(G)), G(G), RG(N), used(N), C(N, -1) {
    for(int i = 0; i < N; i++) {
      for(auto j : G[i]) {
        RG[j].push_back(i);
      }
    }
    
    for(int i = 0; i < N; i++) {
      if(used[i] == 0) {
        dfs(i);
      }
    }

    fill(begin(used), end(used), 0);

    int cnt = 0;
    while(!empty(S)) {
      int u = S.top(); S.pop();
      if(used[u] == 0) {
        scc(u, cnt), cnt++;
      }
    }
  }

  void dfs(int v) {
    used[v] = 1;
    for(auto i : G[v]) {
      if(used[i] == 0) {
        dfs(i);
      }
    }
    S.push(v);
  }

  void scc(int v, int c) {
    used[v] = 1, C[v] = c;
    for(auto i : RG[v]) {
      if(used[i] == 0) {
        scc(i, c);
      }
    }
  }
};/*}}}*/
