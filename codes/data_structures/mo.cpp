const int MAXN = 1e5 + 5;
 
int N;
vector<int> A, M(MAXN, 0);
 
struct Query {
  int l, r, p;
};
vector<int> mo(vector<Query> Q) {
  int sum = 0;
  auto add = [&](int x) -> void {
    
  };
  auto rem = [&](int x) -> void {
    
  };
  int len = sqrt(size(A));
  sort(begin(Q), end(Q), [len](Query const& x, Query const& y) {
    int xlen = x.l / len, ylen = y.l / len;
    if(xlen != ylen) return xlen < ylen;
    return (xlen % 2 == 0 ? x.r < y.r : y.r < x.r);
  });
  int bl = 0, br = -1;
  vector<int> ans(size(Q));
  for(int i = 0; i < size(Q); i++) {
    auto [l, r, p] = Q[i];
    while (br < r) add(++br);
    while (br > r) rem(br--);
    while (bl < l) rem(bl++);
    while (bl > l) add(--bl);
    ans[p] = sum;
  }
  return ans;
}
