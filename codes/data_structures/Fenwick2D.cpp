struct Fenwick2D {
  int n;
  vector<vector<int>> BIT;
 
  Fenwick2D(int n) : n(n), BIT(n + 1, vector<int>(n + 1)) {};
 
  int query(int a, int b) {
    int sum = 0;
    for(int i = a; i > 0; i -= (i & -i)) {
      for (int j = b; j > 0; j -= (j & -j)) {
        sum += BIT[i][j];
      }
    }
    return sum;
  }
 
  void update(int a, int b, int v) {
    for (int i = a; i <= n; i += (i & -i)) {
      for (int j = b; j <= n; j += (j & -j)) {
        BIT[i][j] += v;
      }
    }
  } 
 
  int query(int a, int b, int c, int d) {
    return query(c, d) + query(a - 1, b - 1) - query(c, b - 1) - query(a - 1, d);
  }
};