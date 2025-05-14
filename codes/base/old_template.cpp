#include <bits/stdc++.h>
using namespace std;

// Template (v1.6.0 - 14/05/2025) (ricaxov) {{{
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class X> using ordered_set = tree<X, null_type, less<X>, rb_tree_tag, tree_order_statistics_node_update>;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define int long long
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr)

template<class X> using min_priority_queue = priority_queue<X, vector<X>, greater<X>>;
using ii = pair<int, int>;
using iii = array<int, 3>;
using str = string;
#define V vector

#define all(X) begin(X), end(X)
#define rall(X) rbegin(X), rend(X)
#define sz(X) (int)size(X)

#define pb push_back
#define pf push_front
#define eb emplace_back
#define ef emplace_front
#define ff first
#define ss second

#define each(X, Y) for (auto &X : Y)
#define ceach(X, Y) for (auto const& X : Y)
#define loop(I, L, R) for (int I = L; I <= R; I++)
#define pool(I, R, L) for (int I = R; I >= L; I--)

#define cond(X, Y, Z) (X ? Y : Z)
#define mem(X, Y) memset(X, Y, sizeof(X))
#define inb(X, L, R) (L <= X && X <= R)
#define L1(X...) [&](auto const& x) { return X; }
#define L2(X...) [&](auto const& x, auto const& y) { return X; }

template<class X, class Y> inline bool chmin(X& x, Y y) { return (x > y ? x = y, 1 : 0); }
template<class X, class Y> inline bool chmax(X& x, Y y) { return (x < y ? x = y, 1 : 0); }

int cdiv(int a, int b) { return a/b + ((a^b) > 0 && a % b != 0); }
int fdiv(int a, int b) { return a/b - ((a^b) < 0 && a % b != 0); }

template<class X, class Y> auto& operator >> (istream& is, pair<X, Y>& var) { is >> var.first >> var.second; return is; }
template<class X, class Y> auto& operator << (ostream& os, pair<X, Y> const& var) { os << "(" << var.first << " " << var.second << ")"; return os; }
template<class X> auto& operator >> (istream& is, vector<X>& var) { for (auto &x : var) is >> x; return is; }
template<class X> auto& operator << (ostream& os, vector<X> const& var) { auto sep = ""; for (auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, set<X> const& var) { auto sep = ""; for (auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, multiset<X> const& var) { auto sep = ""; for (auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, unordered_set<X> const& var) { auto sep = ""; for (auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, ordered_set<X> const& var) { auto sep = ""; for (auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, deque<X> const& var) { auto sep = ""; for (auto x : var) os << sep << x, sep = " "; return os; }
template<class X, class Y> auto& operator << (ostream& os, map<X, Y> const& var) { auto sep = ""; for (auto x : var) os << sep << "{" << x.first << " : " << x.second << "}", sep = " "; return os; }
template<class X, class Y> auto& operator << (ostream& os, unordered_map<X, Y> const& var) { auto sep = ""; for (auto x : var) os << sep << "{" << x.first << " : " << x.second << "}", sep = " "; return os; }

template<class...X> void in(X &...x) { ((cin >> x), ...); }
template<class...X> void out(X const&...x) { auto sep = ""; ((cout << sep << x, sep = " "), ...); cout << "\n"; }
template<class...X> void print(X const&...x) { ((cout << x), ...); }
#define var(x) "[", #x, " = ", x, "]"
#ifdef LOCAL
template<class...X> void dbg(X const&...x) { ((cout << x), ...); cout << "\n"; }
#else
template<class...X> void dbg(X const&...x) {}
#endif
//}}}

auto main() -> signed {
  fastio;

  
}
