auto fexp = [&](auto fexp, int b, int e) -> int {
  if(e == 0) return 1;
  int h = fexp(fexp, b, e / 2);
  (h *= h) %= MOD;
  if(e % 2 != 0) (h *= b) %= MOD;
  return h;
};

auto multinv = [&](int x) -> int {
  return fexp(fexp, x, MOD - 2);
};

V<int> fact(MAXN), ifact(MAXN);
fact[0] = 1, ifact[0] = 1;
for(int i = 1; i < MAXN; i++) {
  fact[i] = (i * fact[i - 1]) % MOD;
  ifact[i] = multinv(fact[i]);
}

auto choose = [&](int n, int k) -> int {
  if(n < k) return 0;
  return (((fact[n] * ifact[n - k]) % MOD) * ifact[k]) % MOD;
};