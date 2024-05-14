// Debug {{{
#define var(x) "[", #x, " = ", x, "]"
template<typename...X> void dbg(X const&...x) { ((cout << x), ...); cout << endl; }
//}}}