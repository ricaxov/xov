template<unsigned P> /*{{{*/
struct Z {
  int value;
  Z() : value(0) {}
  Z(int value) : value(((value % P) + P) % P) {}
  
  Z fexp(Z b, int e) {
    if(e == 0) return Z(1);
    Z h = fexp(b, e / 2);
    h = h * h;
    if(e % 2 != 0) h = h * b;
    return h;
  }

  Z operator + (Z m) { return Z(value + m.value); }
  Z operator - (Z m) { return Z(value - m.value); }
  Z operator * (Z m) { return Z(value * m.value); }
  Z operator / (Z m) { return *this * fexp(m, P - 2); }

  bool operator == (Z m) const { return (value == m.value); }

  friend ostream& operator << (ostream& os, Z a) { os << a.value; return os; }
  friend istream& operator >> (istream& is, Z& a) { int x; is >> x; a = Z(x); return is;}
};/*}}}*/
