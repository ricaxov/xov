// Geometry Template (v0.1.0 - 13/05/2024) (ricaxov) {{{
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

// TODO: Check this
/* -1 => Direita  */
/*  0 => Colinear */
/* +1 => Esquerda */

// meu
template<typename T>
int side(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  T x = (b - a) ^ (c - a);
  return (x > EPS) - (x < -EPS);
}

template<typename T>
long double sarea(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  return ((b-a) ^ (c-a))/2.0;
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

// TODO: tem que colocar mais coisas aqui pra cima ^ 

template<typename T>
struct Line {
  Point<T> p1, p2;
  T a, b, c;

  Line () {} /* -> nao sei se vai ter esse construtor quando nao tem nada  */

  // acho que faz mais sentido fazer do p2 pro p1 -> mas isso daqui ta funcionando ent tanto faz
  Line (Point<T> const& p1, Point<T> const& p2) : p1(p1), p2(p2), 
    a(p1.y-p2.y),
    b(p2.x-p1.x), 
    c(p1^p2) {}

  // TODO: terminar isso daqui
  Line (T const& a, T const& b, T const& c) : a(a), b(b), c(c) {
    
  }

  bool operator < (Line const& l) const {
    if (p1 != l.p1) return p1 < l.p1;
    return p2 < l.p2;
  }

  T eval(Point<T> const& p) const {
    return a * p.x + b * p.y + c;
  }

  bool inside(Point<T> const& p) const { // inside line
    return eq(eval(p), T(0));
  }

  // entender essa parte daqui
  bool inside_seg(Point<T> const& p) const {
    return eq(((p1-p) ^ (p2-p)), T())
           && ((p1-p) * (p2-p)) <= T();
  }
};

// essa parte aqui faz total sentido, so precisa desenhar um pouco pra fazer sentido
template<typename T>
bool seg_has_inter(Line<T> const& l1, Line<T> const& l2) {
  if (side(l2.p1, l1.p1, l1.p2) * side(l2.p2, l1.p1, l1.p2) < 0
   && side(l1.p1, l2.p1, l2.p2) * side(l1.p2, l2.p1, l2.p2) < 0) return 1;
  if (l1.inside_seg(l2.p1)) return 1;
  if (l1.inside_seg(l2.p2)) return 1;
  if (l2.inside_seg(l1.p1)) return 1;
  if (l2.inside_seg(l1.p2)) return 1;
  return 0;
}
//}}}
