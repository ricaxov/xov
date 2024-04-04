// Debug {{{
#define var(x) "[", #x, " = ", x, "]"
template<class...X> void dbg(X const&...x) { ((cout << x), ...); cout << "\n"; }
//}}}
