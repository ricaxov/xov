const int MOD = 1e9 + 7;

struct Matrix {
  int N;
  V<V<int>> M;
  Matrix(V<V<int>> P) : N(sz(P)), M(P) {};
  Matrix(int N) : N(N), M(N, V<int>(N)) {};
  Matrix operator * (Matrix const& P) {
    Matrix R(N);
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        for(int k = 0; k < N; k++) {
          (R.M[i][j] += (M[i][k] % MOD * P.M[k][j] % MOD)) %= MOD;
        }
      }
    }
    return R;
  }
};
Matrix fexp(Matrix b, int e) {
  Matrix R(b.N);
  for(int i = 0; i < b.N; i++) R.M[i][i] = 1;
  while(e) {
    if(e & 1) R = R * b;
    e >>= 1, b = b * b;
  }
  return R;
}