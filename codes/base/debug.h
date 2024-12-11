#include <bits/stdc++.h>
using namespace std;

#define int long long

// Debug Base (v1.0 - 21/11/2024) {{{
const string RESET = "\033[0m";
const string BLACK = "\033[30m";
const string WHITE = "\033[37m";

const string RED = "\033[31m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string MAGENTA = "\033[35m";

template<class X, class Y>
auto& operator << (ostream& os, pair<X, Y> const& var) {
  os << "(" << var.first << " " << var.second << ")";
  return os;
}

template<class X> 
auto& operator << (ostream& os, vector<X> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << x, sep = " ";
  }
  return os;
}

template<class X>
auto& operator << (ostream& os, set<X> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << x, sep = " "; 
  }
  return os;
}

template<class X>
auto& operator << (ostream& os, multiset<X> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << x, sep = " ";
  }
  return os;
}

template<class X>
auto& operator << (ostream& os, unordered_set<X> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << x, sep = " "; 
  }
  return os;
}

template<class X>
auto& operator << (ostream& os, deque<X> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << x, sep = " "; 
  }
  return os;
}

template<class X, class Y>
auto& operator << (ostream& os, map<X, Y> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << "{" << x.first << " : " << x.second << "}", sep = " "; 
  }
  return os;
}

template<class X, class Y>
auto& operator << (ostream& os, unordered_map<X, Y> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << "{" << x.first << " : " << x.second << "}", sep = " "; 
  }
  return os;
}

void dbg() { cout << endl; }
template<typename X, typename...Y> void dbg(X x, Y...y) { cout << MAGENTA << " [" << YELLOW << x << MAGENTA << "]"; dbg(y...); }
#define dbg(...) cout << RED << "(" << BLUE <<  #__VA_ARGS__ << RED << "):", dbg(__VA_ARGS__), cout << RESET
//}}}
