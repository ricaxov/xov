// Geometry Template (v1.5.0 - 05/11/2024) (Jotinha, ricaxov, UmMainAkali) - Nacional {{{ 
const long double EPS = 1e-9;
const long double PI = acosl(-1.0);
  
template<typename T>
T sq(T const& x) { return x*x; }
 
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
 
template<typename T> // ang(aôb)
long double angle(Point<T> const& a, Point<T> const& o, Point<T> const& b) {
  long double ang = (a-o) * (b-o) / norm(a-o) / norm(b-o);
  return acosl(max(min(ang, (long double)1), (long double)-1));
}

template<typename T> // ang(cêd) <= ang(aêb) ambos tem e como ponto fixo
bool angle_less(Point<T> const& a, Point<T> const& b, Point<T> const& c,
                                   Point<T> const& d, Point<T> const& e) {
  Point<T> p1{(a-e)*(b-e), abs((a-e)^(b-e))};
  Point<T> p2{(c-e)*(d-e), abs((c-e)^(d-e))};
  return (p2^p1) >= EPS;
};

template<typename T> // reduzir para encontrar número maximo de pontos numa linha
Point<T> reduce(Point<T> const& a) {
  auto gcd = [&](auto &&self, int x, int y) -> int {
    if (y == 0) return x;
    return self(self, y, x%y);
  };
  int g = gcd(gcd, a.x, a.y);
  return {a.x/g, a.y/g};
}

template<typename T> // vetor unitario
Point<T> unit(Point<T> const& a) {
  return a / norm(a);
}
 
template<typename T> // comprimento da projeção de p em (a->b)
T proj_len(Point<T> const& p, Point<T> const& a, Point<T> const& b) {
  T len = (p-a) * (b-a) / norm(b-a);
  return len;
}
 
template<typename T> // projeção de p em (a->b)
Point<T> proj(Point<T> const& p, Point<T> const& a, Point<T> const& b) {
  return a + unit(b-a) * proj_len(p, a, b);
} 
 
/* +1 => Esquerda */
/* -1 => Direita  */
/*  0 => Colinear */
 
template<typename T> // lado do ponto c em relação a (a->b)
int side(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  T x = (b-a) ^ (c-a);
  return (x > EPS) - (x < -EPS);
}
 
template<typename T>
long double sarea(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  return ((b-a)^(c-a))/2;
}
 
template<typename T> // area do triangulo com pts (a, b, c)
long double area(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  return abs(sarea(a, b, c));
}
 
template<typename T> // ccw (a rad)
Point<T> rot(Point<T> const& p, long double const& a) {
  return Point<T>{p.x * cosl(a) - p.y * sinl(a),
                  p.x * sinl(a) + p.y * cosl(a)};
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
  return Point<T>{a.y, a.x};
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
    if (p1 != l.p1) return p1 < l.p1;
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

template<typename T> // tem inter de segs (l1, l2)
bool seg_has_inter(Line<T> const& l1, Line<T> const& l2) {
  if (side(l2.p1, l1.p1, l1.p2) * side(l2.p2, l1.p1, l1.p2) < 0
   && side(l1.p1, l2.p1, l2.p2) * side(l1.p2, l2.p1, l2.p2) < 0) return 1;
  if (l1.inside_seg(l2.p1)) return 1;
  if (l1.inside_seg(l2.p2)) return 1;
  if (l2.inside_seg(l1.p1)) return 1;
  if (l2.inside_seg(l1.p2)) return 1;
  return 0;
}

template<typename T> // pt de inter de retas (l1, l2)
vector<Point<T>> inter_line(Line<T> const& l1, Line<T> const& l2) {
  auto det = l1.a*l2.b - l1.b*l2.a;
  if (eq(det, T())) return {};
  auto x = (l1.b*l2.c - l1.c*l2.b)/det;
  auto y = (l1.c*l2.a - l1.a*l2.c)/det;
  return {Point<T>{x, y}};
}

template<typename T>
vector<Point<T>> inter_seg_proper(Line<T> const& l1, Line<T> const& l2) {
  auto ans = inter_line(l1, l2);
  if (ans.empty()) return {};
  if (!l1.inside_seg(ans.front())) return {};
  if (!l2.inside_seg(ans.front())) return {};
  return ans;
}

template<typename T> // seg inter
vector<Point<T>> inter_seg(Line<T> const& l1, Line<T> const& l2) {
  if (!seg_has_inter(l1, l2)) return {};

  vector<Point<T>> ps;
  if (l1.inside_seg(l2.p1)) ps.push_back(l2.p1);
  if (l1.inside_seg(l2.p2)) ps.push_back(l2.p2);
  if (l2.inside_seg(l1.p1)) ps.push_back(l1.p1);
  if (l2.inside_seg(l1.p2)) ps.push_back(l1.p2);

  sort(begin(ps), end(ps));
  ps.erase(unique(begin(ps), end(ps)), end(ps));

  if (size(ps) == 1) return {ps.front()};
  else if (size(ps) > 1) return {ps.front(), ps.back()};

  return {inter_seg_proper(l1, l2).front()};
}

template<typename T> // dist pt e reta
T point_line_dist(Point<T> const& p, Line<T> const& l) {
  if (l.p1 == l.p2) return norm(l.p1-p);
  return 2 * abs(sarea(p, l.p1, l.p2)) / norm(l.p1-l.p2);
}

template<typename T> // dist pt e seg
T point_seg_dist(Point<T> const& p, Line<T> const& l) {
  if (l.p1 == l.p2) return norm(l.p1-p);
  if ((l.p2-l.p1)*(p-l.p1) < 0) return norm(l.p1-p);
  if ((l.p1-l.p2)*(p-l.p2) < 0) return norm(l.p2-p);
  return point_line_dist(p, l);
}

template<typename T> // dist segs
T seg_dist(Line<T> const& l1, Line<T> const& l2) {
  if (seg_has_inter(l1, l2)) return T();
  return min({point_seg_dist(l1.p1, l2),
              point_seg_dist(l1.p2, l2),
              point_seg_dist(l2.p1, l1),
              point_seg_dist(l2.p2, l1)});
}

template<typename T>
struct Circle {
  T r;
  Point<T> c;
  Circle (Point<T> const& c, T const& r) : c(c), r(r) {}
  bool inside (Point<T> const& a) const {
    return norm(a-c) <= r + EPS;
  }
};

template<typename T> // pts de inter entre circ
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

template<typename T> // area de inter entre circ (r1 >= r2)
T circle_inter_area(Circle<T> const& c1, Circle<T> const& c2) {
  T d = norm(c1.c, c2.c);

  if (d >= c1.r+c2.r) return T();
  if (d <= c1.r-c2.r) return PI*c2.r*c2.r;

  T ang1 = 2*acosl((c2.r*c2.r - c1.r*c1.r - d*d) / (-2*c1.r*d));
  T ang2 = 2*acosl((c1.r*c1.r - c2.r*c2.r - d*d) / (-2*c2.r*d));
  T a1 = ang1*c1.r*c1.r/2 - c1.r*c1.r*sinl(ang1)/2;
  T a2 = ang2*c2.r*c2.r/2 - c2.r*c2.r*sinl(ang2)/2;

  return a1+a2;
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
 
template<typename T> // poly area
long double area(Poly<T> const& P) {
  return abs(sarea(P));
}

// CH sem pts colineares
template<typename T>
Poly<T> convex_hull(Poly<T> P) {
  sort(begin(P), end(P));
 
  vector<Point<T>> L, U;
  for (auto p : P) {
    while (size(L) >= 2 && side(p, end(L)[-2], end(L)[-1]) != +1) L.pop_back();
    L.push_back(p);
  }
  reverse(begin(P), end(P));
  for (auto p : P) {
    while (size(U) >= 2 && side(p, end(U)[-2], end(U)[-1]) != +1) U.pop_back();
    U.push_back(p);
  }
  L.pop_back();
  L.insert(end(L), begin(U), end(U)-1);
  return L;
}
 
template<typename T> // par com menor dist (euclidiana)
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

template<typename T> // pts int no seg l
int points_in_seg(Line<T> const& l) {
  return gcd(abs(l.p1.x-l.p2.x), abs(l.p1.y-l.p2.y));
}

// pick -> (area = inside + boundary/2 - 1)
// (pts int inside e boundary de P)
template<typename T>
pair<int, int> pick(Poly<T> const& P) { // ccw
  int N = size(P);
  int area = 0, boundary = 0;
  for (int i = 0; i < N; i++) {
    auto cp = P[i], np = P[(i+1)%N];
    area += cp^np, boundary += points_in_seg(Line{cp, np});
  }
  int inside = (abs(area)-boundary+2) / 2;
  return {inside, boundary};
}

template<typename T> // ccw (sort pelo ang)
void polar_sort(vector<Point<T>>& P) {
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

template<typename T> // ccw
bool inside(Point<T> const& p, Point<T> const& a, Point<T> const& b, Point<T> const& c) {
  int x = side(p, a, b);
  int y = side(p, b, c);
  int z = side(p, c, a);
  return !((x == +1 || y == +1 || z == +1) && (x == -1 || y == -1 || z == -1));
}

template<typename T> // pt num poly convexo
bool inside_convex(Point<T> const& p, Poly<T> const& poly) { // ccw 
  int bl = 2, br = size(poly)-1;
  while (bl < br) {
    int bm = (bl+br)/2;
    if (side(p, poly[0], poly[bm]) == +1) bl = bm+1;
    else br = bm;
  }
  return inside(p, poly[0], poly[br-1], poly[br]);
}

enum Where {
  Inside = 1,
  Outside = -1,
  Boundary = 0,
};

template<typename T> // pt num poly simples (convexo ou não)
Where inside(Point<T> const& p, Poly<T> const& A) { // ccw
  int N = size(A), w = 0;
  for (int i = 0; i < N; i++) {
    if (p == A[i]) return Boundary;
    int j = (i+1)%N;
    if (A[i].y == p.y && A[j].y == p.y) {
      if (min(A[i].x, A[j].x) <= p.x && p.x <= max(A[i].x, A[j].x)) {
        return Boundary;
      }
    } else {
      bool ibelow = A[i].y < p.y;
      bool jbelow = A[j].y < p.y;
      if (ibelow != jbelow) {
        auto o = side(p, A[i], A[j]);
        if (o == 0) return Boundary;
        if (ibelow == (o > 0)) w += (ibelow ? +1 : -1);
      }
    }
  }
  return (w ? Inside : Outside);
}
//}}}
