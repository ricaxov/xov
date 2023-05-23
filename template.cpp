#include <bits/stdc++.h>
using namespace std;

//Template (v1.0.0 - 2023-04-27) (ricaxov) {{{
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class X> using ordered_set = tree<X, null_type, less<X>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr)

template<class X> using V = vector<X>;
template<class X> using min_priority_queue = priority_queue<X, vector<X>, greater<X>>;
using ii = pair<int, int>;
using iii = array<int, 3>;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define xov "┌( ಠ_ಠ)┘"
#define mem(x, y) memset(x, y, sizeof(x))
#define inbounds(x, l, r) (l <= x && x <= r)
#define fillin freopen("in.txt", "r", stdin)
#define fillout freopen("out.txt", "w", stdout)
#define L1(x...) [&](auto X) { return x; }
#define L2(x...) [&](auto X, auto Y) { return x; }

template<class X, class Y> auto& operator >> (istream& is, pair<X, Y>& var) { is >> var.ff >> var.ss; return is; }
template<class X, class Y> auto& operator << (ostream& os, pair<X, Y> const& var) { os << "(" << var.ff << " " << var.ss << ")"; return os; }
template<class X> auto& operator >> (istream& is, vector<X>& var) { for(auto &x : var) is >> x; return is; }
template<class X> auto& operator << (ostream& os, vector<X> const& var) { auto sep = ""; for(auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, set<X> const& var) { auto sep = ""; for(auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, multiset<X> const& var) { auto sep = ""; for(auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, unordered_set<X> const& var) { auto sep = ""; for(auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, ordered_set<X> const& var) { auto sep = ""; for(auto x : var) os << sep << x, sep = " "; return os; }
template<class X> auto& operator << (ostream& os, deque<X> const& var) { auto sep = ""; for(auto x : var) os << sep << x, sep = " "; return os; }
template<class X, class Y> auto& operator << (ostream& os, map<X, Y> const& var) { auto sep = ""; for(auto x : var) os << sep << "{" << x.ff << " : " << x.ss << "}", sep = " "; return os; }
template<class X, class Y> auto& operator << (ostream& os, unordered_map<X, Y> const& var) { auto sep = ""; for(auto x : var) os << sep << "{" << x.ff << " : " << x.ss << "}", sep = " "; return os; }

template<class...X> void in(X &...x) { ((cin >> x), ...); }
template<class...X> void out(X const&...x) { auto sep = ""; ((cout << sep << x, sep = " "), ...); cout << "\n"; }
template<class...X> void print(X const&...x) { ((cout << x), ...); }

void dbg() { cerr << "\n"; }
template<typename X, typename...Y> void dbg(X x, Y...y) { cerr << " " << x; dbg(y...); }
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", dbg(__VA_ARGS__), cerr << "\n"
//}}}

auto main() -> signed {
  fastio;
  
}
