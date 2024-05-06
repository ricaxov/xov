// Hashed String {{{
struct HashedString {
  static const int M = (1LL << 61) - 1;
  static const int B;
  static vector<int> P;

  int N;
  vector<int> H;

  __int128 mul(int a, int b) { return (__int128)a * b; }
  int mod_mul(int a, int b) { return mul(a, b) % M; }

  explicit HashedString(string const& S) : H(size(S) + 1), N(size(S)) {
    while (size(P) < size(S) + 1) P.push_back(mod_mul(P.back(), B));

    H[0] = 0;
    for (int i = 0; i < size(S); i++) {
      H[i + 1] = (mul(H[i], B) + S[i]) % M;
    }
  }

  int get_hash(int l, int r) {
    int R = H[r + 1] - mod_mul(H[l], P[r - l + 1]);
    return (R + M) % M;
  }
};
vector<int> HashedString::P{1};
mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());
const int HashedString::B = uniform_int_distribution<int>(0, M - 1)(rng);
//}}}
