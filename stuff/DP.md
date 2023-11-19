# Aula de DP - by xov 😎

## Pré-requisitos

> $Recursão$
>
> ![Percurso](https://b2316719.smushcdn.com/2316719/wp-content/uploads/2022/11/dfs_animated-1.gif?size=1200x693&lossy=1&strip=1&webp=1)

> $Recorrência$
>
>![Árvore](https://i.stack.imgur.com/QVSdv.png)
>
>![Recorrência](https://www.fatalerrors.org/images/blog/87a71d9c97ecc4c6d0d936adab430b04.jpg)

## Vocabulário

> $Estados: \ Partes \ importantes \ do \ problema \ que \ devem \ ser \ salvas.$
>
> $DP[i][j] \ mantem \ a \ resposta \ para \ o \ nosso \ problema, \ onde:$ <br>
> $i = qual \ elemento \ está \ sendo \ avaliado$ <br>
> $j = a \ capacidade \ de \ armazenamento \ restante$

> $Transições: \ Interação \ entre \ os \ Estados.$ <br>
>
> $DP[i][j] = DP[i - 1][j]$ <br>
> $DP[i][j] = max(DP[i][j], \ DP[i - 1][j - C[i - 1]] + P[i - 1]), \ para \ j \ >= C[i - 1]$

> $Casos \ Base: \ Caso \ com \ resposta \ conhecida.$<br>
>
> $DP[i][0] = 0$ <br>
> $DP[0][j] = 0$

## Estilos de DP:

> $Top-Down:$ <br>
>
> - $Memoization$
> - $Recursivo$
> - $Armazena \ os \ subproblemas \ para \ evitar \ recálculo$

> $Bottom-Up:$ <br>
>
> - $Tabulation$
> - $Iterativo$
> - $Resolver \ os \ subproblemas \ menores \ e \ acumula \ as \ respostas \ ate \ chegar \ no \ problema \ como \ um \ todo$

## Curiosidade:
> $Push \ DP: \ DP[i + 1] = DP[i]$ <br>
> $Pull \ DP: \ DP[i] = DP[i - 1]$



## Problemas

### [Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a)

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

### [Vacation](https://atcoder.jp/contests/dp/tasks/dp_c)

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

### [Knapsack 1](https://atcoder.jp/contests/dp/tasks/dp_d)

```c++
signed main() {
  int N, W; cin >> N >> W;
  vector<int> C(N), P(N);
  for(int i = 0; i < N; i++) {
    cin >> C[i] >> P[i];
  }

  vector<vector<int>> DP(N + 1, vector<int>(W + 1));
  
  for(int i = 0; i <= N; i++) DP[i][0] = 0;
  for(int i = 0; i <= W; i++) DP[0][i] = 0;

  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= W; j++) {
      DP[i][j] = DP[i - 1][j];
      if(j >= C[i - 1]) {
        DP[i][j] = max(DP[i][j], DP[i - 1][j - C[i - 1]] + P[i - 1]);
      }
    }
  }

  cout << DP[N][W] << '\n';
}
```

```c++
int N, W;
vector<int> C, P;
vector<vector<int>> DP;

int f(int cur, int qnt) {
  if(cur == N || qnt == 0) return 0;
  if(DP[cur][qnt] != -1) return DP[cur][qnt];

  int ans = f(cur + 1, qnt);
  if(qnt >= C[cur]) {
    ans = max(ans, f(cur + 1, qnt - C[cur]) + P[cur]);
  }

  return DP[cur][qnt] = ans;
}
signed main() {   
  cin >> N >> W;
  
  C.resize(N), P.resize(N);
  DP.assign(N + 1, vector<int>(W + 1, -1));
  for(int i = 0; i < N; i++) {
    cin >> C[i] >> P[i];
  }

  cout << f(0, W) << '\n';
}
```

### [Minimizing Coins](https://cses.fi/problemset/task/1634/)

```c++
const int INF = 1e18;
 
signed main() {
  int N, W; cin >> N >> W;
  vector<int> v(N);
  for(auto &i : v) cin >> i;
 
  vector<int> DP(W + 1, INF);
  DP[0] = 0;
 
  for(int i = 0; i <= W; i++) {
    for(int j = 0; j < N; j++) {
      if(i + v[j] <= W) {
        DP[i + v[j]] = min(DP[i + v[j]], DP[i] + 1);
      }
    }
  }
 
  cout << (DP[W] == INF ? -1 : DP[W]) << '\n';
}
```
