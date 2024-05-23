// suffix array O(Nlog(N)) -> NÃO TERMINEI DE ARRUMAR, NEM DE TESTAR

// Suffix Array {{{
vector<int> sort_cyclic_shifts(string const& S) {
  int N = size(S);

  vector<int> p(N), c(N), cnt(max(1LL << 8, N));

  for (auto i : S) cnt[i]++;
  partial_sum(begin(cnt), end(cnt), begin(cnt));

  for (int i = 0; i < N; i++) {
    p[--cnt[S[i]]] = i;
  }

  c[p[0]] = 0;

  int classes = 1;
  for (int i = 1; i < N; i++) {
    if (S[p[i]] != S[p[i - 1]]) classes++;
    c[p[i]] = classes - 1;
  }

  vector<int> pn(N), cn(N);
  for (int shift = 1; shift < N; shift *= 2) {
    for (int i = 0; i < N; i++) {
      pn[i] = p[i] - shift;
      if (pn[i] < 0) pn[i] += N;
    }

    fill(begin(cnt), begin(cnt) + classes, 0);

    for (int i = 0; i < N; i++) cnt[c[pn[i]]]++;
    for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
    for (int i = N - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
    cn[p[0]]= 0;
    classes = 1;

    auto key = [&](int x) {
      return pair{c[x], c[(x + shift) % N]};
    };
    
    for (int i = 1; i < N; i++) {
      if (key(p[i]) != key(p[i - 1])) classes++;
      cn[p[i]] = classes - 1;
    }

    c.swap(cn);
  }
  return p;
}
vector<int> kasai(string const& S, vector<int> const& P) {
  int N = size(S);
  vector<int> rank(N);
  for (int i = 0; i < N; i++) {
    rank[P[i]] = i;
  }

  int k = 0;
  vector<int> lcp(N - 1);
  for (int i = 0; i < N; i++) {
    if (rank[i] == N - 1) {
      k = 0;
    } else {
      int j = P[rank[i] + 1];
      while (i + k < N && j + k < N && S[i + k] == S[j + k]) k++;
      lcp[rank[i]] = k;
      if (k) k--;
    }
  }

  return lcp;
}
//}}}
