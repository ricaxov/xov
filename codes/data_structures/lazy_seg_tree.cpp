template<typename T>/*{{{*/
struct LazySegmentTree {
  int N;
  vector<T> data, lazy;
  explicit LazySegmentTree(int N) : N(N), data(4 * N), lazy(4 * N, 0) {}
 
  T merge(T a, T b) {
    return a + b;
  }
 
  void apply(int p, int l, int r) {
    if(lazy[p] != 0) {
      data[p] += lazy[p];
      if(l != r) {
        lazy[2 * p] += lazy[p];
        lazy[2 * p + 1] += lazy[p];
      }
      lazy[p] = 0;
    }
  }
 
  T set(int x, int y, T const& v, int p, int l, int r) {
    apply(p, l, r);
    if(x <= l && r <= y) {
      lazy[p] += v;
      apply(p, l, r);
      return data[p];
    }
    if(y < l || r < x) return data[p];
    int m = midpoint(l, r);
    return data[p] = merge(set(x, y, v, 2 * p, l, m), set(x, y, v, 2 * p + 1, m + 1, r));
  }
 
  T get(int x, int y, int p, int l, int r) {
    apply(p, l, r);
    if(x <= l && r <= y) return data[p];
    if(y < l || r < x) return 0;
    int m = midpoint(l, r);
    return merge(get(x, y, 2 * p, l, m), get(x, y, 2 * p + 1, m + 1, r));
  }
 
  T set(int x, int y, T v) { return set(x, y, v, 1, 0, N - 1); }
  T get(int x, int y) { return get(x, y, 1, 0, N - 1); }
};/*}}}*/
