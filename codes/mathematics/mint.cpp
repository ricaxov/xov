const int MOD = 998'244'353;

template<unsigned P> struct Z {
  unsigned value;
  constexpr Z() : value(0) {}
  template<typename T, typename = enable_if_t<is_integral<T>::value>> constexpr Z(T a) : value((((long long)a % P) + P) % P) {}
  Z& operator += (Z rhs) { value += rhs.value; if(value >= P) value -= P; return *this; }
  Z& operator -= (Z rhs) { value += P - rhs.value; if(value >= P) value -= P; return *this; }
  Z& operator *= (Z rhs) { value = (unsigned long long)value * rhs.value % P;return *this; }
  Z& operator /= (Z rhs) { return *this *= pow(rhs, -1); }
  Z operator + () const { return *this; }
  Z operator - () const { return Z() - *this; }
  bool operator == (Z rhs) const { return value == rhs.value; }
  bool operator != (Z rhs) const { return value != rhs.value; }
  friend Z operator + (Z lhs, Z rhs) { return lhs += rhs; }
  friend Z operator - (Z lhs, Z rhs) { return lhs -= rhs; }
  friend Z operator * (Z lhs, Z rhs) { return lhs *= rhs; }
  friend Z operator / (Z lhs, Z rhs) { return lhs /= rhs; }
  friend auto& operator << (ostream& os, Z a) { return os << a.value; }
  friend auto& operator >> (istream& is, Z& a) { long long value; is >> value; a = Z(value); return is; }
};
template<unsigned P> Z<P> pow(Z<P> x, long long p) {
  if(x == 0) return (p == 0 ? 1 : 0);
  p %= P - 1;
  if(p < 0) p += P - 1;
  Z<P> res = 1;
  while(p) {
    if(p & 1) res *= x;
    x *= x, p >>= 1;
  }
  return res;
}

using mint = Z<MOD>;