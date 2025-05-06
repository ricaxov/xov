vector<int> linear_mobius(int N) {
  vector<bool> composite(N+1, 0);
  vector<int> mobius(N+1), primes;
  mobius[1] = 1;

  for (int i = 2; i <= N; i++) {
    if (!composite[i]) {
      primes.emplace_back(i);
      mobius[i] = -1;
    }
  
    for (auto p : primes) {
      if (i*p > N) break;
      composite[i*p] = 1;
  
      if (i % p == 0) {
        mobius[i*p] = 0;
        break;
      } else {
        mobius[i*p] = -mobius[i];
      }
    }
  }

  return mobius;
}
