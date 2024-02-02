// Fenwick Tree {{{
struct FenwickTree {
  int N;
  vector<int> data;
  explicit FenwickTree(int N) : N(N), data(N) {}

  void add(int idx, int delta) {
    for(int i = idx; i < N; i |= (i + 1)) {
      data[i] += delta;
    }
  }

  int sum(int r) {
    int ret = 0;
    for (int i = r; i >= 0; i &= (i + 1), i--) {
      ret += data[i];
    }
    return ret;
  }

  int sum(int l, int r) {
    return sum(r) - sum(l - 1);
  }
};
//}}}