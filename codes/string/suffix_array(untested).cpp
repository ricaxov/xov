// suffix array O(Nlog(N)) -> NÃO TERMINEI DE ARRUMAR, NEM DE TESTAR

// Suffix Array {{{
vector<int> sort_cyclic_shifts(string const& S) {
  const int MALPHA = 256;
  int N = size(S);

  vector<int> p(N), c(N), cnt(max(MALPHA, N), 0);
  for (int i = 0; i < N; i++) cnt[S[i]]++;

  partial_sum(begin(cnt), end(cnt), begin(cnt));

  for (int i = N - 1; i >= 0; i--) {
    p[--cnt[S[i]]] = i;
  }

  c[p[0]] = 0;

  int classes = 1;
  for (int i = 1; i < N; i++) {
    if (S[p[i]]  != S[p[i - 1]]) classes++;
    c[p[i]] = classes-1;
  }

  vector<int> pn(N), cn(N);

  for (int h = 0; (1 << h) < N; h++) {
    for (int i = 0; i < N; i++) {
      pn[i] = p[i] - (1<<h);
      if (pn[i] < 0) pn[i] += N;
    }

    fill(begin(cnt), begin(cnt) + classes, 0);

    for (int i = 0; i < N; i++) cnt[c[pn[i]]]++;
    for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
    for (int i = N-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
    cn[p[0]]= 0;
    classes = 1;

    for (int i = 1; i < N; i++) {
      pair cur{c[p[i]], c[(p[i] + (1 << h)) % N]};
      pair prev{c[p[i-1]], c[(p[i-1] + (1 << h)) % N]};

      if (cur != prev) classes++;
      cn[p[i]] = classes - 1;
    }

    c.swap(cn);
  }
  return p;
}
//}}}
