const int MAXN = 1e5 + 5;
 
int cur;
V<int> v, occ(MAXN, 0);
 
struct Query {
  int l, r, p;
};
 
void add(int x) {

}
void rem(int x) {
  
}
 
V<int> mo(V<Query> queries) {
  int bs = sqrt(sz(v));
  sort(all(queries), [bs](const Query& x, const Query& y) {
    int bx = x.l / bs, by = y.l / bs;
    if(bx != by) return bx < by;
    return (bx % 2 == 0 ? x.r < y.r : y.r < x.r);
  });
  int bl = 0, br = -1;
  V<int> ans(sz(queries));
  for(int i = 0; i < sz(queries); i++) {
    auto [l, r, p] = queries[i];
    while (br < r) add(++br);
    while (br > r) rem(br--);
    while (bl < l) rem(bl++);
    while (bl > l) add(--bl);
    ans[p] = cur;
  }
  return ans;
}