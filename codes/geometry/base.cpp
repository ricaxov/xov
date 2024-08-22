// Geometry Template (v0.5.5 - 22/08/2024) (Jotinha, ricaxov, UmMainAkali) {{{
const long double EPS = 1e-9;
const long double PI = acosl(-1.0);
  
template<typename T>
T sq(T x) { return x*x; }
 
template<typename T>
bool eq(T const& a, T const& b) {
  return abs(a-b) <= EPS;
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
 
  Point operator + (Point const& p) const { return {x+p.x, y+p.y}; }
  Point operator - (Point const& p) const { return {x-p.x, y-p.y}; }
  Point operator * (T const& d) const { return {x*d, y*d}; }
  Point operator / (T const& d) const { return {x/d, y/d}; }
  T operator * (Point const& p) const { return x*p.x + y*p.y; }
  T operator ^ (Point const& p) const { return x*p.y - y*p.x; }
  
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
long double norm(Point<T> const& a) {
  return sqrtl(a * a);
}
 
template<typename T>
long double norm(Point<T> const& a, Point<T> const& b) {
  return norm(a-b);
}
 
template<typename T>
T norm2(Point<T> const& a) {
  return a * a;
}
 
template<typename T>
T norm2(Point<T> const& a, Point<T> const& b) {
  return norm2(a-b);
}
 
template<typename T>
Point<T> unit(Point<T> const& a) {
  return a / norm(a);
}
 
template<typename T>
T proj_len(Point<T> const& p, Point<T> const& a, Point<T> const& b) {
  T len = (p-a) * (b-a) / norm(b-a);
  return len;
}
 
template<typename T>
Point<T> proj(Point<T> const& p, Point<T> const& a, Point<T> const& b) {
  return a + unit(b-a) * proj_len(p, a, b);
} 
 
/* +1 => Left */
/* -1 => Right  */
/*  0 => Collinear */
 
template<typename T>
int side(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  T x = (b-a) ^ (c-a);
  return (x > EPS) - (x < -EPS);
}
 
template<typename T>
long double sarea(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  return ((b-a)^(c-a))/2;
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
Point<T> rot90cw(Point<T> const& a) {
  return Point<T>{a.y, -a.x};
}
 
template<typename T>
Point<T> rot90ccw(Point<T> const& a) {
  return Point<T>{-a.y, a.x};
}
 
template<typename T>
Point<T> transp(Point<T> const& a) {
  return Point{a.y, a.x};
}
 
template<typename T>
struct Line {
  T a, b, c;
  Point<T> p1, p2;
 
  Line () {}
 
  Line (Point<T> const& p1, Point<T> const& p2) : p1(p1), p2(p2),
    a(p1.y-p2.y),
    b(p2.x-p1.x), 
    c(p1^p2) {}
 
  bool operator < (Line const& l) const {
    if (!eq(p1, l.p1)) return p1 < l.p1;
    return p2 < l.p2;
  }
 
  T eval(Point<T> const& p) const {
    return a*p.x + b*p.y + c;
  }
 
  bool inside(Point<T> const& p) const {
    return eq(eval(p), T());
  }
 
  bool inside_seg(Point<T> const& p) const {
    return (eq((p1-p) ^ (p2-p), T()) 
           && ((p1-p) * (p2-p) <= EPS)); 
  }
};
 
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
 
template<typename T>
struct Circle {
  T r;
  Point<T> c;
  Circle (Point<T> const& c,  T r) : c(c), r(r) {}
  bool inside(Point<T> const& a) const {
    return norm(a-c) <= r + EPS;
  }
};
 
template<typename T>
vector<Point<T>> inter_circle(Circle<T> const& c1, Circle<T> const& c2) {
  if (c1.c == c2.c) return {};
  Point vec = c2.c - c1.c;
  T d2 = vec * vec;
  T sum = c1.r + c2.r;
  T dif = c1.r - c2.r;
  T p = (d2 + c1.r * c1.r - c2.r * c2.r) / (2 * d2);
  T h2 = c1.r * c1.r - p * p * d2;
  if (sum * sum < d2 || dif * dif > d2) return {};
  Point mid = c1.c + vec*p;
  Point per = Point(-vec.y, vec.x) * sqrtl(max(T(), h2) / d2);
  if (per == Point<T>()) return {mid};
  return {mid + per, mid - per};
}
 
template<typename T>
using Poly = vector<Point<T>>;
 
template<typename T>
long double sarea(Poly<T> const& P) {
  int N = size(P);
  long double area = 0;
  for (int i = 0; i < N; i++) {
    auto cp = P[i], np = P[(i+1)%N];
    area += cp^np;
  }
  return area/2;
}
 
template<typename T>
long double area(Poly<T> const& P) {
  return abs(sarea(P));
}
 
template<typename T>
Poly<T> convex_hull(Poly<T> P) {
  sort(begin(P), end(P));
 
  vector<Point<T>> L, U;
  for (auto p : P) {
    while (size(L) >= 2 && side(p, end(L)[-2], end(L)[-1]) != 1) L.pop_back();
    L.push_back(p);
  }
  reverse(begin(P), end(P));
  for (auto p : P) {
    while (size(U) >= 2 && side(p, end(U)[-2], end(U)[-1]) != 1) U.pop_back();
    U.push_back(p);
  }
  L.pop_back();
  L.insert(end(L), begin(U), end(U)-1);
  return L;
}
 
template<typename T>
pair<Point<T>, Point<T>> closest_pair(vector<Point<T>> P) {
  const long double CP_INF = 1e18;
 
  pair<long double, pair<Point<T>, Point<T>>> best;
  best.first = CP_INF;
 
  set<Point<T>> S;
  sort(begin(P), end(P));
 
  int il = 0;
  for (int ir = 0; ir < size(P); ir++) {
    if (ir != 0 && P[ir] == P[ir-1]) return {P[ir], P[ir-1]};
    while (P[ir].x-P[il].x >= best.first) {
      S.erase(transp(P[il]));
      il++;
    }
    for (auto it = S.upper_bound({P[ir].y-best.first, CP_INF});
              it != end(S) && it->x < P[ir].y+best.first; it++) {
      auto p = transp(*it);
      best = min(best, {norm(P[ir], p), pair{P[ir], p}});
    }
    S.insert(transp(P[ir]));
  }
  return best.second;
}

template<typename T>
int points_in_line(Line<T> l) {
  return gcd(abs(l.p1.x-l.p2.x), abs(l.p1.y-l.p2.y));
}

template<typename T>
pair<int, int> pick(Poly<T> P) {
  int N = size(P);
  int area = 0, boundary = 0;
  for (int i = 0; i < N; i++) {
    auto cp = P[i], np = P[(i+1)%N];
    area += cp^np, boundary += points_in_line(Line{cp, np});
  }
  int inside = (abs(area)-boundary+2) / 2;
  return {inside, boundary};
}

template<typename T>
long double angle(Point<T> const& a, Point<T> const& o, Point<T> const& b) {
  long double ang = (a-o) * (b-o) / norm(a-o) / norm(b-o);
  return acos(max(min(ang, (long double)1), (long double)-1));
}

/* must be integral T */

template<typename T>
Point<T> reduce(Point<T> const& a) {
  auto gcd = [&](auto &&self, int x, int y) {
    if (y == 0) return x;
    return self(self, y, x%y);
  };
  int g = gcd(gcd, a.x, a.y);
  return {a.x/g, a.y/g};
}

template<typename T>
void polar_sort(vector<Point<T>>& P) { // ccw
  auto sign = [&](T const& a) -> int {
    return (a > EPS) - (a < -EPS);
  };

  auto half = [&](Point<T> const& a) -> int {
    return (!eq(a.y, T()) ? sign(a.y) : -sign(a.x));
  };

  sort(begin(P), end(P), [&](Point<T> const& a, Point<T> const& b) {
    int ha = half(a), hb = half(b);
    return (ha == hb ? (a^b) > 0 : ha < hb);
  });
}
//}}}
