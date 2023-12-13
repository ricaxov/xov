template<typename T>
class SegmentTree {
  int N;
  vector<T> SEG;
public:
  explicit SegmentTree(vector<T> const& V) : N(size(V)), SEG(2 * N) {
    for(int i = 0; i < N; i++) {
      SEG[i + N] = V[i];
    }
    for(int i = N - 1; i > 0; i--) {
      SEG[i] = min(SEG[2 * i], SEG[2 * i + 1]);
    }
  }
  void set(int p, T value) {
    for(SEG[p += N] = value, p /= 2; p > 0; p /= 2) {
      SEG[p] = min(SEG[2 * p], SEG[2 * p + 1]);
    }
  }
  T min(int l, int r) {
    T res = 1e18;
    for(l += N, r += N + 1; l < r; l /= 2, r /= 2) {
      if(l % 2 != 0) res = min(res, SEG[l++]);
      if(r % 2 != 0) res = min(res, SEG[--r]);
    }
    return res;
  }
};
