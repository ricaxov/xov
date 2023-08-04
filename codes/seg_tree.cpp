template<typename T> class SegmentTree {
  int n;
  V<T> SEG;
  T neutral;
  function<T(T,T)> merge;
public:
  SegmentTree(int n, T neutral, function<T(T,T)> merge) : n(n), neutral(neutral), merge(merge), SEG(2 * n, neutral) {};

  SegmentTree(V<T> &v, T neutral, function<T(T,T)> merge) : n(sz(v)), neutral(neutral), merge(merge), SEG(2 * n, neutral) {
    for(int i = 0; i < n; i++) {
      SEG[i + n] = v[i];
    }
    build();
  }

  void build() {
    for(int i = n - 1; i > 0; i--) {
      SEG[i] = merge(ST[2 * i], ST[2 * i + 1]);
    }
  }

  T query(int l, int r) {
    T rl = neutral, rr = neutral;
    for(l += n, r += n + 1; l < r; l /= 2, r /= 2) {
      if(l & 1) rl = merge(rl, SEG[l++]);
      if(r & 1) rr = merge(SEG[--r], rr);
    }
    return merge(rl, rr);
  }

  void update(int p, T val) {
    for(SEG[p += n] = val; p > 1; p /= 2) {
      SEG[p / 2] = merge(SEG[min(p, p ^ 1)], SEG[max(p, p ^ 1)]);
    }
  }
};
