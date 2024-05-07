// Inside Boundary {{{
template<typename T>
bool inbounds(T x, T l, T r) {
  return (l <= x && x <= r);
}
//}}}
