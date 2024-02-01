struct Hash {
  static int mix(int x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(int x) const {
    static const int w = chrono::steady_clock::now().time_since_epoch().count();
    return mix(x + w);
  }
};