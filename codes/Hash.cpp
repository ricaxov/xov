const int M1 = 1000015553, M2 = 1000028537;
mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());
const int B1 = uniform_int_distribution<int>(356, M1 - 1)(rng), B2 = uniform_int_distribution<int>(356, M2 - 1)(rng);
 
// Hashed String {{{ 
struct HashedString {
  int N;
  string S;
  vector<int> H1, P1, H2, P2;
 
  explicit HashedString() : N(0) {}
  explicit HashedString(string const& S) : N(size(S)), S(S), H1(N, S[0]), P1(N, 1), H2(N, S[0]), P2(N, 1) {
    for(int i = 1; i < N; i++) {
      P1[i] = (P1[i - 1] * B1) % M1, P2[i] = (P2[i - 1] * B2) % M2;
      H1[i] = (H1[i - 1] * B1 + S[i]) % M1, H2[i] = (H2[i - 1] * B2 + S[i]) % M2;
    }
  }
  int get(int l, int r) {
    if(l == 0) return ((H1[r] << 30) ^ (H2[r]));
    int R1 = (((H1[r] - (H1[l - 1] * P1[r - l + 1])) % M1) + M1) % M1;
    int R2 = (((H2[r] - (H2[l - 1] * P2[r - l + 1])) % M2) + M2) % M2;
    return ((R1 << 30) ^ (R2));
  }
};
//}}}