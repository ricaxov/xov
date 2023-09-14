struct Point {
  int x, y;
  bool operator < (Point p) { return (x < p.x || (x == p.x && y < p.y)); };
};
 
int orientation(Point o, Point a, Point b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
 
V<Point> Hull(V<Point> v) {
  int n = sz(v), k = 0;
  
  if(n <= 3) return v;
  
  V<Point> H(2 * n);
  sort(all(v));
  
  for(int i = 0; i < n; i++) {
    while((k >= 2) && orientation(H[k - 2], H[k - 1], v[i]) < 0) k--;
    H[k++] = v[i];
  }
  for(int i = n - 1, t = k + 1; i > 0; i--) {
    while(k >= t && orientation(H[k - 2], H[k - 1], v[i - 1]) < 0) k--;
    H[k++] = v[i - 1];
  }
  
  H.resize(k - 1);
  return H;
}
