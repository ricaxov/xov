// Mo's Algorithm {{{
const int BLK = 400;
struct MoQuery {
  int l, r, idx;
  bool operator < (MoQuery const& o) const {
    if (l/BLK != o.l/BLK) return l < o.l;
    if (l/BLK % 2 == 0) return r < o.r;
    else return r > o.r;
  }
};
//}}}

auto add = [&](int x) {
    
};
auto rem = [&](int x) {
  
};

int bl = 0, br = -1;
vector<bool> ans(size(Q));
for (int i = 0; i < size(Q); i++) {
  auto [l, r, p] = Q[i];
  while (br < r) add(++br);
  while (br > r) rem(br--);
  while (bl < l) rem(bl++);
  while (bl > l) add(--bl);
  ans[p] = ANSWER;
}
