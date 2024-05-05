// Matrix {{{
struct Matrix {
  int L, C;
  vector<vector<int>> M;
  const int MOD = 1e9 + 7;  
  explicit Matrix(int const& L, int const& C) : L(L), C(C), M(L, vector<int>(C, 0)) {}
  explicit Matrix(vector<vector<int>> const& M) : L(size(M)), C(size(M[0])), M(M) {}
 
  Matrix operator * (Matrix const& K) const {
    int W = size(K.M[0]);
    Matrix R(L, W);
    for (int i = 0; i < L; i++) {
      for (int j = 0; j < W; j++) {
        for (int k = 0; k < C; k++) {
          (R.M[i][j] += (M[i][k] % MOD) * (K.M[k][j] % MOD)) %= MOD;
        }
      }
    }
    return R;
  }
 
  bool operator == (Matrix const& K) const {
    if (L != size(K.M) || C != size(K.M[0])) return 0;
 
    bool eq = 1;
    for (int i = 0; i < L; i++) {
      for (int j = 0; j < C; j++) {
        eq &= (M[i][j] == K.M[i][j]);
      }
    }
    return eq;
  }
};
// TODO: add matrix_fexp
//}}}
