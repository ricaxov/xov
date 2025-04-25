struct point {
  int x, y, z;
  point () : x(0), y(0), z(0) {}
  point (int nx, int ny, int nz) : x(nx), y(ny), z(nz) {}
};
 
bool eq(int const& a, int const& b) {
  return a == b;
}
 
bool operator < (point const& a, point const& b) {
  if (!eq(a.x, b.x)) return a.x < b.x;
  if (!eq(a.y, b.y)) return a.y < b.y;
  return a.z < b.z;
}
 
bool operator == (point const& a, point const& b) { return eq(a.x, b.x) && eq(a.y, b.y) && eq(a.z, b.z); }
point operator - (point const& a, point const& b) { return point{a.x-b.x, a.y-b.y, a.z-b.z}; }
int operator * (point const& a, point const& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
int norm(point const& a) { return a*a; }
 
bool on_x(point const& a, point const& b) { return a.x < b.x; }
bool on_y(point const& a, point const& b) { return a.y < b.y; }
bool on_z(point const& a, point const& b) { return a.z < b.z; }
 
struct Node {
  const int MAXIS = 1e9;
 
  point p;
  int x0 = MAXIS, x1 = -MAXIS, y0 = MAXIS, y1 = -MAXIS, z0 = MAXIS, z1 = -MAXIS;
  Node *first = nullptr, *second = nullptr;
  
  int dist(point const& cp) {
    int x = (cp.x < x0 ? x0 : cp.x > x1 ? x1 : cp.x);
    int y = (cp.y < y0 ? y0 : cp.y > y1 ? y1 : cp.y);
    int z = (cp.z < z0 ? z0 : cp.z > z1 ? z1 : cp.z);
    return norm(point{x, y, z}-cp);
  }
 
  Node(vector<point>&& points) : p(points.front()) {
    for (auto cp : points) {
      x0 = min(x0, cp.x), x1 = max(x1, cp.x);
      y0 = min(y0, cp.y), y1 = max(y1, cp.y);
      z0 = min(z0, cp.z), z1 = max(z1, cp.z);
    }
    if (size(points) >= 2) {
      auto cmp = ((x1-x0 >= y1-y0 && x1-x0 >= z1-z0) ? on_x : ((y1-y0 >= z1-z0) ? on_y : on_z));
      sort(begin(points), end(points), cmp);
 
      int half = size(points)/2;
      first = new Node({begin(points), begin(points)+half});
      second = new Node({begin(points)+half, end(points)});
    }
  }
};
 
struct KDTree {
  const int CP_INF = 1e18;
 
  Node* root;
  KDTree(vector<point> const& points) : root(new Node({begin(points), end(points)})) {}
 
  pair<int, point> search(Node *node, point const& cp) {
    if (node->first == nullptr) {
      if (cp == node->p) return {CP_INF, point()}; // uncomment if we should not find the point itself
      return pair{norm(cp-node->p), node->p};
    }
 
    Node *f = node->first, *s = node->second;
    int bf = f->dist(cp), bs = s->dist(cp);
    if (bf > bs) swap(bs, bf), swap(f, s);
 
    auto best = search(f, cp);
    if (bs < best.first) best = min(best, search(s, cp));
    return best;
  }
 
  pair<int, point> closest(point const& p) { // requires an operator < for points
    return search(root, p);
  }
};
