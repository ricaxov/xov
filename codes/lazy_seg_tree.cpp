// needs fixing
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
  SegmentTree(int n) : n(n), SEG(4 * n), LAZY(4 * n, 0) {};
  SegmentTree(vector<T> const& v) : n((int)v.size()), SEG(4 * n), LAZY(4 * n, 0) {
    neutral = 0;
    build(0, n - 1, 1, v);
  }
  T query(int x, int y) { return query(0, n - 1, 1, x, y); }
  void update(int x, int y, T v) { update(0, n - 1, 1, x, y, v); }
};
