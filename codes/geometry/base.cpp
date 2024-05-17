// Geometry Template (v0.2.0 - 16/05/2024) (ricaxov) {{{
const long double EPS = 1e-9;
const long double PI = acos(-1.0);

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

template<typename T>
Point<T> unit(Point<T> const& a) {
  return a / norm(a);
}

/* +1 => Left */
/* -1 => Right  */
/*  0 => Collinear */

template<typename T>
int side(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  T x = (b - a) ^ (c - a);
  return (x > EPS) - (x < -EPS);
}

template<typename T>
long double sarea(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  return ((b - a) ^ (c - a)) / 2.0;
}

template<typename T>
long double area(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  return abs(sarea(a, b, c));
}

template<typename T>
Point<T> rot(Point<T> const& p, long double a) { // ccw
  return Point<T>{p.x * cos(a) - p.y * sin(a),
                  p.x * sin(a) + p.y * cos(a)};
}

template<typename T>
Point<T> rot90cw(Point<T> const& p) {
  return Point<T>{p.y, -p.x};
}

template<typename T>
Point<T> rot90ccw(Point<T> const& p) {
  return Point<T>{-p.y, p.x};
}

template<typename T>
struct Line {
  T a, b, c;
  Point<T> p1, p2;

  // Line () : {}

  Line (Point<T> const& p1, Point<T> const& p2) : p1(p1), p2(p2),
    a(p1.y - p2.y),
    b(p2.x - p1.x), 
    c(p1 ^ p2) {}

  Line (T const& a, T const& b, T const& c) : a(a), b(b), c(c) {}
    // !WARN: missing this part

  bool operator < (Line const& l) const {
    if (p1 != l.p1) return p1 < l.p1;
    return p2 < l.p2;
  }

  T eval(Point<T> const& p) const {
    return a * p.x + b * p.y + c;
  }

  bool inside(Point<T> const& p) const {
    return eq(eval(p), T(0));
  }

  bool inside_seg(Point<T> const& p) const {
    return (eq((p1 - p) ^ (p2 - p), T(0)) 
           && ((p1 - p) * (p2 - p) <= T(0))); 
  }
};
//}}}