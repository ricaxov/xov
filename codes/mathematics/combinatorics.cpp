// Modular Arithmetic {{{
template<unsigned P>
struct Z {
  unsigned value;

  constexpr Z() : value(0) {}
  
  constexpr Z(int x) : value(((x%P)+P)%P) {}
  
  Z& operator += (Z m) {
    value += m.value;
    if (value >= P) value -= P;
    return *this;
  }

  Z& operator -= (Z m) {
    value += P - m.value;
    if (value >= P) value -= P;
    return *this;
  }

  Z& operator *= (Z m) {
    value = (unsigned int)value * m.value % P;
    return *this;
  }

  Z& operator /= (Z m) { 
    return *this *= pow(m, -1);
  }

  Z operator + () const { return *this; }

  Z operator - () const { return Z() - *this; }

  bool operator == (Z m) const { return value == m.value; }

  bool operator != (Z m) const { return value != m.value; }

  friend Z operator + (Z l, Z m) { return l += m; }

  friend Z operator - (Z l, Z m) { return l -= m; }

  friend Z operator * (Z l, Z m) { return l *= m; }

  friend Z operator / (Z l, Z m) { return l /= m; }
  
  friend ostream& operator << (ostream& os, Z a) { os << a.value; return os; }
  
  friend istream& operator >> (istream& is, Z& a) { int x; is >> x; a = Z(x); return is; }
};

template<unsigned P>
Z<P> pow(Z<P> b, int e) {
  if (b == 0) return e == 0 ? 1 : 0;
  e %= P-1;
  if (e < 0) e += P-1;

  Z<P> ans = 1;
  while (e) {
    if (e & 1) ans *= b;
    b *= b, e >>= 1;
  }
  return ans;
}
//}}}

// Combinatorics {{{
template <unsigned P>
struct Combinatorics {
  vector<Z<P>> fact, ifact;

  explicit Combinatorics(int N) : fact(N), ifact(N) {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i-1] * i;
    ifact[N-1] = 1 / fact[N-1];
    for (int i = N-1; i-1 >= 0; i--) ifact[i-1] = ifact[i] * i;
  }

  Z<P> C(int n, int k) const {
    if (k < 0 || n < k) return 0;
    return fact[n] * ifact[k] * ifact[n-k];
  }
};
//}}}
