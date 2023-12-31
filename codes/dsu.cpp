// DSU {{{
struct DSU {
  vector<int> P, S;
  explicit DSU(int N) : P(N, -1), S(N, 1) {};
  int leader(int v) {
    if(P[v] == -1) return v;
    return P[v] = leader(P[v]);
  }
  int merge(int a, int b) {
    a = leader(a), b = leader(b);
    if(a != b) {
      if(S[a] < S[b]) swap(a, b);
      P[b] = a, S[a] += S[b];
    }
    return a;
  }
  bool same(int a, int b) {
    return leader(a) == leader(b);
  }
};
//}}}
