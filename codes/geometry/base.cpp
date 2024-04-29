// Geometry Template (v0.0.6 - 28/04/2024) (ricaxov) {{{
const long double EPS = 1e-9;
const long double PI = acos(-1.0);
 
template<typename T>
T sq(T x) { return x * x; }
 
template<typename T>
bool eq(T const& a, T const& b) {
  return abs(a - b) <= EPS;
}
 
template<>
bool eq<int>(int const& a, int const& b) {
  return a == b;
}
 
template<typename T>
struct Point {
  T x, y;
  Point() : x(0), y(0) {}
  Point(T x, T y) : x(x), y(y) {}
 
  Point operator + (Point const& p) const { return {x + p.x, y + p.y}; }
  Point operator - (Point const& p) const { return {x - p.x, y - p.y}; }
  Point operator * (T const& d) const { return {x * d, y * d}; }
  Point operator / (T const& d) const { return {x / d, y / d}; }
  T operator * (Point const& p) const { return x * p.x + y * p.y; }
  T operator ^ (Point const& p) const { return x * p.y - y * p.x; }
 
  bool operator < (Point const& p) const {
    if (!eq(x, p.x)) return x < p.x;
    return y < p.y;
  }
 
  bool operator == (Point const& p) const {
    return (eq(x, p.x) && eq(y, p.y));
  }
 
  bool operator != (Point const& p) const {
    return !(*this == p);
  }
 
  friend istream& operator >> (istream& is, Point& p) { return is >> p.x >> p.y; }
  friend ostream& operator << (ostream& os, Point const& p) { return os << p.x << ' ' << p.y; }
};
 
template<typename T>
long double norm(Point<T> const& x) {
  return sqrtl(x * x);
}
 
template<typename T>
T norm2(Point<T> const& x) {
  return x * x;
}
 
// Preciso verificar isso daqui, dps
/* -1 => Direita  */
/*  0 => Colinear */
/* +1 => Esquerda */
 
template<typename T>
int side(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  T x = (b-a) ^ (c-a);
  return (x > EPS) - (x < -EPS);
}
 
template<typename T>
long double sarea(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  return ((b-a) ^ (c-a)) / 2.0;
}
 
template<typename T>
long double area(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  return abs(sarea(a, b, c));
}
 
// TODO: Line
// TODO: Poly
// TODO: CH
//}}}
