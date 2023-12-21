#include <bits/stdc++.h>
using namespace std;

#define int long long

// Segment Tree - v.0.5.0 {{{
template<typename T>
class SegmentTree {
private:
  int N;
  vector<T> A, S, L;
  T neutral, unmarked;
public:
  explicit SegmentTree(int N, T const& neutral, T const& unmarked) : N(N), S(4 * N), L(4 * N, unmarked), neutral(neutral), unmarked(unmarked) {}
  explicit SegmentTree(vector<T> A, T const& neutral, T const& unmarked) : N(size(A)), A(A), S(4 * N), L(4 * N, unmarked), neutral(neutral), unmarked(unmarked) { 
    for(int i = 0; i < N; i++) {
      set(i, i, A[i]);
    }
  } 

  void apply(int p, int l, int r) {
    if(L[p] != unmarked) {
      // S[p] = L[p];
      if (l != r) {
        // L[2 * p] = L[p];
        // L[2 * p + 1] = L[p];
      }
      L[p] = unmarked;
    }
  }

  T get(int a, int b, int p, int l, int r) {
    apply(p, l, r);
    if(a <= l && r <= b) return S[p];
    if(b < l || r < a) return neutral;
    return get(a, b, 2 * p, l, midpoint(l, r)) + get(a, b, 2 * p + 1, midpoint(l, r) + 1, r);
  }

  T set(int a, int b, T const& x, int p, int l, int r) {
    apply(p, l, r);
    if(a <= l && r <= b) {
      L[p] = x;
      apply(p, l, r);
      return S[p];
    }
    if(b < l || r < a) return S[p];
    return S[p] = set(a, b, x, 2 * p, l, midpoint(l, r)) + set(a, b, x, 2 * p + 1, midpoint(l, r) + 1, r);
  }

  T get(int a, int b) { return get(a, b, 1, 0, N - 1); }
  T set(int a, int b, T const& x) { return set(a, b, x, 1, 0, N - 1); }
};
//}}}

struct Node {
  int A;
  Node() : A(0) {}
  Node(int A) : A(A) {}
  Node operator + (Node N) const {
    return A + N.A;
  }
  bool operator != (Node N) const {
    return A != N.A;
  }
};

const Node neutral, unmarked;

// auto main() -> signed {
//   ios_base::sync_with_stdio(false); cin.tie(nullptr);


// }
