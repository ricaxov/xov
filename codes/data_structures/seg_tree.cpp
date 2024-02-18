template<typename T> /*{{{*/
struct SegmentTree {
  int N;
  T Neutral;
  vector<T> data;
  explicit SegmentTree (int N) : N(N), data(4 * N) {}

  T merge(T a, T b) {
    return a + b;
  }

  T set(int x, T const& v, int p, int l, int r) {
    if(l == x && x == r) return data[p] = v;
    if(x < l || r < x) return data[p];
    int m = midpoint(l, r);
    return data[p] = merge(set(x, v, 2 * p, l, m), set(x, v, 2 * p + 1, m + 1, r));
  }

  T get(int x, int y, int p, int l, int r) {
    if(x <= l && r <= y) return data[p];
    if(y < l || r < x) return T();
    int m = midpoint(l, r);
    return merge(get(x, y, 2 * p, l, m), get(x, y, 2 * p + 1, m + 1, r));
  }

  T set(int x, T v) { return set(x, v, 1, 0, N - 1); }
  T get(int x, int y) { return get(x, y, 1, 0, N - 1); }
};/*}}}*/
