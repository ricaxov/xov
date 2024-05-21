// Fast Fourier Transform {{{
const int MOD = 998244353;
using cd = complex<double>;
const double PI = acos(-1.0);

void fft(vector<cd>& A) {
  int N = size(A), L = 31 - __builtin_clz(N);
  static vector<complex<long double>> R(2, 1);
	static vector<cd> rt(2, 1);

  for (static int k = 2; k < N; k *= 2) {
		R.resize(N);
		rt.resize(N);
		auto x = polar(1.0L, acos(-1.0L) / k);
    for (int i = k; i < 2*k; i++) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
	}
  vector<int> rev(N);
  for (int i = 0; i < N; i++) rev[i] = (rev[i/2] | (i&1) << L)/2;
  for (int i = 0; i < N; i++) if (i < rev[i]) swap(A[i], A[rev[i]]);

  for (int k = 1; k < N; k *= 2) {
    for (int i = 0; i < N; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        auto x = (double *)&rt[j + k];
        auto y = (double *)&A[i + j + k];

        cd z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
        A[i + j + k] = A[i + j] - z;
				A[i + j] += z;
      }
    }
  }
}

vector<int> convolution(vector<int> const& A, vector<int> const& B) {
  if (empty(A) || empty(B)) return {};

  vector<int> ans(size(A) + size(B) - 1);
  int K = 32 - __builtin_clz(size(ans)), N = 1 << K, cut = sqrt(MOD);
	vector<cd> L(N), R(N), outs(N), outl(N);

	for (int i = 0; i < size(A); i++) L[i] = cd((int)A[i] / cut, (int)A[i] % cut);
	for (int i = 0; i < size(B); i++) R[i] = cd((int)B[i] / cut, (int)B[i] % cut);

	fft(L), fft(R);
  
  for (int i = 0; i < N; i++) {
		int j = -i & (N - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * N);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * N) / 1i;
	}

	fft(outl), fft(outs);

	for (int i = 0; i < size(ans); i++) {
		int av = (int)(real(outl[i]) + 0.5), cv = (int)(imag(outs[i]) + 0.5);
		int bv = (int)(imag(outl[i]) + 0.5) + (int)(real(outs[i]) + 0.5);
		ans[i] = ((av % MOD * cut + bv) % MOD * cut + cv) % MOD;
	}
	return ans;
}
//}}}
