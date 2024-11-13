#include <bits/stdc++.h>
using namespace std;

#define int long long

// TODO: Colored Output

// Debug Base {{{
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

template<class X> auto& operator << (ostream& os, multiset<X> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << x, sep = " ";
  }
  return os;
}

template<class X> auto& operator << (ostream& os, unordered_set<X> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << x, sep = " "; 
  }
  return os;
}

template<class X> auto& operator << (ostream& os, deque<X> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << x, sep = " "; 
  }
  return os;
}

template<class X, class Y> auto& operator << (ostream& os, map<X, Y> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << "{" << x.first << " : " << x.second << "}", sep = " "; 
  }
  return os;
}

template<class X, class Y> auto& operator << (ostream& os, unordered_map<X, Y> const& var) { 
  auto sep = "";
  for (auto x : var) {
    os << sep << "{" << x.first << " : " << x.second << "}", sep = " "; 
  }
  return os;
}

string remove_spaces(string line) {
  reverse(begin(line), end(line));
  while (line.back() == ' ') line.pop_back();
  reverse(begin(line), end(line));
  return line;
}

void dbg_out() { cout << endl; }

template <typename X, typename... Y>
void dbg_out(string line, X x, Y... y) {
  auto idx = line.find(',');
  cout << "[" << line.substr(0, idx) << " = " << x << "] ";
  if (idx != string::npos) {
    line = remove_spaces(line.substr(idx+1));
    if constexpr (sizeof...(y) > 0) dbg_out(line, y...);
  } else {
    dbg_out();
  }
}

#define dbg(...) dbg_out(#__VA_ARGS__, __VA_ARGS__)
//}}}
