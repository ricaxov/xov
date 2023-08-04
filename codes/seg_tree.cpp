template<typename T> class SegmentTree {
  int n;
  T neutral;
  V<T> ST;
  function<T(T,T)> merge;
public:
  SegmentTree(int n, T neutral, function<T(T,T)> merge) : n(n), neutral(neutral), merge(merge), ST(2 * n, neutral) {};

  SegmentTree(V<T> &v, T neutral, function<T(T,T)> merge) : n(sz(v)), neutral(neutral), merge(merge), ST(2 * n, neutral) {
    for(int i = 0; i < n; i++) {
      ST[i + n] = v[i];
    }
    build();
  }

  void build() {
    for(int i = n - 1; i > 0; i--) {
      ST[i] = merge(ST[2 * i], ST[2 * i + 1]);
    }
  }

  T query(int l, int r) {
    T rl = neutral, rr = neutral;
    for(l += n, r += n + 1; l < r; l /= 2, r /= 2) {
      if(l & 1) rl = merge(rl, ST[l++]);
      if(r & 1) rr = merge(ST[--r], rr);
    }
    return merge(rl, rr);
  }

  void update(int p, T val) {
    for(ST[p += n] = val; p > 1; p /= 2) {
      ST[p / 2] = merge(ST[min(p, p ^ 1)], ST[max(p, p ^ 1)]);
    }
  }
};