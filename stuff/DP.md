# Aula de DP - by ricas 😎

### Preciso revisar ainda

# Pre requisitos

## Recursão

# Conceitos

## Recorrência

![Árvore](https://i.stack.imgur.com/QVSdv.png)

![Recorrência](https://www.fatalerrors.org/images/blog/87a71d9c97ecc4c6d0d936adab430b04.jpg)

## Estados

## Transição

## Casos Base


# Problemas

## [Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a)

```c++
const int INF = 1e18;

auto main() -> signed {
  int N; cin >> N;

  vector<int> H(N);
  for(auto &i : H) cin >> i;

  vector<int> DP(N, INF);
  DP[0] = 0;

  for(int i = 0; i < N; i++) {
    if(i + 1 < N) DP[i + 1] = min(DP[i + 1], DP[i] + abs(H[i] - H[i + 1]));
    if(i + 2 < N) DP[i + 2] = min(DP[i + 2], DP[i] + abs(H[i] - H[i + 2]));
  }

  cout << DP[N - 1] << '\n';
}
```

```c++
const int INF = 1e18;

int N;
vector<int> H, DP;

int f(int rock) {
  if(rock == N - 1) return 0;
  if(DP[rock] != -1) return DP[rock];

  int ans = INF;
  if(rock + 1 < N) ans = min(ans, f(rock + 1) + abs(H[rock] - H[rock + 1]));
  if(rock + 2 < N) ans = min(ans, f(rock + 2) + abs(H[rock] - H[rock + 2]));

  return DP[rock] = ans;
}
signed main() {
  cin >> N;

  DP.assign(N, -1), H.resize(N);
  for(auto &i : H) cin >> i;

  cout << f(0) << '\n';
}
```

## [Vacation](https://atcoder.jp/contests/dp/tasks/dp_c)

```c++
signed main() {
  int N; cin >> N;

  vector<vector<int>> DP(N + 1, vector<int>(3));
  DP[0][0] = DP[0][1] = DP[0][2] = 0;

  for(int i = 0; i < N; i++) {
    int A, B, C; cin >> A >> B >> C;
    DP[i + 1][0] = max(DP[i][1] + B, DP[i][2] + C);
    DP[i + 1][1] = max(DP[i][0] + A, DP[i][2] + C);
    DP[i + 1][2] = max(DP[i][0] + A, DP[i][1] + B);
  }

  cout << *max_element(begin(DP[N]), end(DP[N])) << '\n';
}
```

```c++
int N;
vector<vector<int>> V, DP;

int f(int day, int last) {
  if(day == N) return 0;
  if(DP[day][last] != -1) return DP[day][last];

  int A = 0, B = 0, C = 0;

  if(last == 0) A = f(day + 1, 1) + V[day][0], B = f(day + 1, 2) + V[day][1], C = f(day + 1, 3) + V[day][2];
  if(last == 1) B = f(day + 1, 2) + V[day][1], C = f(day + 1, 3) + V[day][2];
  if(last == 2) A = f(day + 1, 1) + V[day][0], C = f(day + 1, 3) + V[day][2];
  if(last == 3) A = f(day + 1, 1) + V[day][0], B = f(day + 1, 2) + V[day][1];

  return DP[day][last] = max({A, B, C});
}
signed main() {
  cin >> N;

  DP.assign(N + 1, vector<int>(4, -1)), V.assign(N, vector<int>(3));

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < 3; j++) {
      cin >> V[i][j];
    }
  }

  cout << f(0, 0) << '\n';
}
```

## [Coins](https://atcoder.jp/contests/dp/tasks/dp_i)

```c++
signed main() {
  int N; cin >> N;

  vector<double> P(N);
  for(auto &i : P) cin >> i;

  vector<vector<double>> DP(N + 1, vector<double>(N + 1));
  DP[0][0] = 1.0;

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      DP[i + 1][j] += DP[i][j] * (1.0 - P[i]);
      DP[i + 1][j + 1] += DP[i][j] * P[i];
    }
  }

  double ans = 0;
  for(int i = N; i >= (N + 1) / 2; i--) {
    ans += DP[N][i];
  }

  cout.precision(10);
  cout.setf(ios::fixed);
  cout << ans << '\n';
}
```

```c++
int N;
vector<double> P;
vector<vector<double>> DP;

double f(int i, int j) {
  if(j >= (N + 1) / 2) return 1.0;
  if(i == N) return 0.0;
  if(DP[i][j] != -1) return DP[i][j];
  return DP[i][j] = f(i + 1, j) * (1.0 - P[i]) + f(i + 1, j + 1) * P[i];
}
signed main() {
  cin >> N;

  DP.assign(N + 1, vector<double>(N + 1, -1)), P.resize(N);
  
  for(auto &i : P) cin >> i;

  cout.precision(10);
  cout.setf(ios::fixed);
  cout << f(0, 0) << '\n';
}
```

## [Minimizing Coins](https://cses.fi/problemset/task/1634/)

```c++
const int INF = 1e9;
 
signed main() {
  int N, M; cin >> N >> M;
  vector<int> V(N);
  for(auto &i : V) cin >> i;

  vector<int> DP(M + 1, INF);
  DP[0] = 0;
  
  for(int i = 0; i < N; i++) {
    for(int j = 0; j <= M; j++) {
      if(j + V[i] <= M) {
        DP[j + V[i]] = min(DP[j + V[i]], DP[j] + 1);
      }
    }
  }

  cout << (DP[M] == INF ? -1 : DP[M]) << '\n';
}
```
