using Node = iii;
const int MAXN = 1e5 + 5, INF = 1e18;
 
enum Info {
  Q = 0,
  M = 1,
  G = 2
};
 
int N;
V<int> A;
V<Node> T(4 * MAXN);
 
Node merge(Node L, Node R) {
  if(L[M] < R[M]) return {L[Q], L[M], gcd(L[G], R[G])};
  else if(L[M] > R[M]) return {R[Q], R[M], gcd(R[G], L[G])};
  return {L[Q] + R[Q], L[M], gcd(R[G], L[G])};
}
Node build(int p = 1, int l = 0, int r = N - 1) {
  if(l == r) return T[p] = {1, A[l], A[l]};
  return T[p] = merge(build(2 * p, l, midpoint(l, r)), 
                      build(2 * p + 1, midpoint(l, r) + 1, r)); 
}
Node query(int x, int y, int p = 1, int l = 0, int r = N - 1) {
  if(x <= l && r <= y) return T[p];
  if(l > y || r < x) return {0, INF, 0};
  return merge(query(x, y, 2 * p, l, midpoint(l, r)),
               query(x, y, 2 * p + 1, midpoint(l, r) + 1, r)); 
}