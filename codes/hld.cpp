template<typename T> class SegmentTree {
private:
  int n;
  T neutral;
  vector<T> SEG, LAZY;
  T merge(T a, T b) {
    return a + b;
  }
  void apply(int p, bool c) {
    if(LAZY[p]) {
      SEG[p] += LAZY[p];
      if(c) LAZY[2 * p] += LAZY[p], LAZY[2 * p + 1] += LAZY[p];
      LAZY[p] = 0;
    }
  }
  void build(int l, int r, int p, vector<T> const& v) {
    if(l == r) {
      SEG[p] = v[l]; return;
    }
    int m = (l + r) / 2;
    build(l, m, 2 * p, v);
    build(m + 1, r, 2 * p + 1, v);
    SEG[p] = merge(SEG[2 * p], SEG[2 * p + 1]);
  }
  T query(int l, int r, int p, int a, int b) {
    apply(p, r - l);
    if(a > r || b < l) return neutral;
    if(l >= a && r <= b) return SEG[p];
    int m = (l + r) / 2;
    return merge(query(l, m, 2 * p, a, b), query(m + 1, r, 2 * p + 1, a, b));
  }
  void update(int l, int r, int p, int a, int b, T x) {
    apply(p, r - l);
    if(a > r || b < l) return;
    if(l >= a && r <= b) {
      LAZY[p] = x;
      apply(p, r - l);
      return;
    }
    int m = (l + r) / 2;
    update(l, m, 2 * p, a, b, x);
    update(m + 1, r, 2 * p + 1, a, b, x);
    SEG[p] = merge(SEG[2 * p], SEG[2 * p + 1]);
  }
public:
  SegmentTree() {}
  SegmentTree(vector<T> const& v) : n((int)v.size()), SEG(4 * n), LAZY(4 * n, 0) {
    neutral = 0;
    build(0, n - 1, 1, v);
  }
  T query(int x, int y) { return query(0, n - 1, 1, x, y); }
  void update(int x, int y, T v) { update(0, n - 1, 1, x, y, v); }
};
 
template<typename T> struct HLD {
  int TIMER;
  SegmentTree<T> SEG;
  vector<vector<pair<int, T>>> G;
  vector<T> sv, tmp, leader, par, pos, tree_sz;
  
  HLD() {}
  HLD(int n) : G(n + 1), leader(n + 1), par(n + 1), pos(n + 1), tree_sz(n + 1), sv(n + 1), tmp(n + 1) {};
 
  void add_edge(int u, int v, T w) {
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  void build(int root = 0) {
    TIMER = 0;
    leader[root] = root;
    dfs(root); hld(root);
    SEG = SegmentTree<T>(tmp);
  }
  void hld(int u, int p = -1) {
    pos[u] = TIMER++;
    tmp[pos[u]] = sv[u];
    for(auto &i : G[u]) {
      auto [v, w] = i;
      if (v == p) continue;
      par[v] = u;
      leader[v] = (i == G[u][0] ? leader[u] : v);
      hld(v, u);
    }
  }
  void dfs(int u, int p = -1) {
    tree_sz[u] = 1;
    for(auto &i : G[u]) {
      auto [v, w] = i;
      if (p == v) continue;
      dfs(v, u);
      sv[v] = w;
      tree_sz[u] += tree_sz[v];
      if(tree_sz[v] > tree_sz[G[u][0].first] || G[u][0].first == p) {
        swap(i, G[u][0]);
      }
    }
  }
  int query_path(int u, int v){
    if (u == v) return 0;
    if (pos[u] < pos[v]) swap(u, v);
    if (leader[u] == leader[v]) return SEG.query(pos[v] + 1, pos[u]);
    return SEG.query(pos[leader[u]], pos[u]) + query_path(par[leader[u]], v);
  }
  void update_path(int u, int v, int val){
    if(u == v) return;
    if(pos[u] < pos[v]) swap(u, v);
    if(leader[u] == leader[v]) {
      SEG.update(pos[v] + 1, pos[u], val); return;
    }
    SEG.update(pos[leader[u]], pos[u], val); 
    update_path(par[leader[u]], v, val);
  }
  int lca(int u, int v) {
    if(pos[u] < pos[v]) swap(u, v);
    return (leader[u] == leader[v] ? v : lca(par[leader[u]], v));
  }
  int query_subtree(int a) {
    if(tree_sz[a] == 1) return 0;
    return SEG.query(pos[a] + 1, pos[a] + tree_sz[a] - 1);
  }
  void update_subtree(int a, int x) {
    if(tree_sz[a] == 1) return;
    SEG.update(pos[a] + 1, pos[a] + tree_sz[a] - 1, x);
  }
};
