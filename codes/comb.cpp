// Still need to fix some things

const int MAXN = 1e5 + 5, MOD = 998'244'353;

vector<int> fact(MAXN), ifact(MAXN);
int fexp(int b, int e) {
  if(e == 0) return 1;
  int h = fexp(b, e / 2); (h *= h) %= MOD;
  if(e & 1) (h *= b) %= MOD;
  return h; 
}
int multinv(int x) {
  return fexp(x, MOD - 2);
}
int choose(int n, int k) {
  if(n < k) return 0;
  return (((fact[n] * ifact[k]) % MOD) * ifact[n - k]) % MOD;
}
auto main() -> signed {
  fastio;
  
  for(int i = 0; i < MAXN; i++) {
    if(i == 0) fact[i] = 1;
    else fact[i] = (i * fact[i - 1]) % MOD;
    ifact[i] = multinv(fact[i]);
  }
}
