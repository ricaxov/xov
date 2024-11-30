// Sieve of Eratosthenes {{{
vector<int> sieve(int N) {
  vector<bool> prime(N, 1);
  prime[0] = prime[1] = 0;

  vector<int> P;
  for(int i = 2; i < N; i++) {
    if(prime[i] == 1) {
      P.emplace_back(i);
      for(int j = i * i; j < N; j += i) {
        prime[j] = 0;
      }
    }
  }
  return P;
}
//}}}

const int MAXN = 2e5 + 5;
auto primes = sieve(MAXN);

// Prime Factorization {{{
vector<pair<int, int>> factorize(int N) {
  vector<pair<int, int>> F;
  for(auto p : primes) {
    if(p * p > N) break;
    if(N % p == 0) {
      F.emplace_back(p, 0);
      auto &[a, b] = F.back();
      while(N % a == 0) N /= a, b++;
    }
  }
  if(N > 1) F.emplace_back(N, 1);
  return F;
}
//}}}
