// Z_P (Modular Arithmetic) {{{
template <unsigned P>
struct Z {
  unsigned value;

  constexpr Z() : value(0) {}

  template<typename T, typename = enable_if_t<is_integral<T>::value>>
  constexpr Z(T rhs) : value(((rhs % P) + P) % P) {}

  Z& operator += (Z rhs) {
    value += rhs.value;
    if (value >= P) value -= P;
    return *this;
  }

  Z& operator -= (Z rhs) {
    value += P - rhs.value;
    if (value >= P) value -= P;
    return *this;
  }

  Z& operator *= (Z rhs) {
    value = ((unsigned int)value * rhs.value) % P;
    return *this;
  }

  Z& operator /= (Z rhs) { return *this *= pow(rhs, -1); }

  Z operator + () const { return *this; }

  Z operator - () const { return Z() - *this; }

  bool operator == (Z rhs) const { return value == rhs.value; }

  bool operator != (Z rhs) const { return value != rhs.value; }

  friend Z operator + (Z lhs, Z rhs) { return lhs += rhs; }

  friend Z operator - (Z lhs, Z rhs) { return lhs -= rhs; }

  friend Z operator * (Z lhs, Z rhs) { return lhs *= rhs; }

  friend Z operator / (Z lhs, Z rhs) { return lhs /= rhs; }

  friend ostream& operator << (ostream& out, Z rhs) { return out << rhs.value; }

  friend istream& operator >> (istream& in, Z& rhs) { int x; in >> x, rhs = Z(x); return in; }
};

template<unsigned P>
Z<P> pow(Z<P> x, int p) {
  if (x == 0) return (p == 0 ? 1 : 0);

  p %= P-1;
  if (p < 0) p += P-1;
  
  Z<P> res = 1;
  while (p > 0) {
    if (p % 2 != 0) res *= x;
    x *= x, p /= 2;
  }

  return res;
}
//}}}
