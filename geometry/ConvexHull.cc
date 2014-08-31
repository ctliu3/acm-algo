struct Point {
  double x;
  double y;
  Point(double x = 0, double y = 0): x(x), y(y) {
  }

  Point operator-(const Point& o) {
    return Point(x - o.x, y - o.y);
  }

  bool operator<(const Point& o) const {
    if (x != o.x) {
      return x < o.x;
    }
    return y < o.y;
  }

  int cross(const Point o) {
    return x * o.y - y * o.x;
  }
};

vector<Point> graham_scan(vector<Point>& points) {
  int n = (int)points.size();
  if (n < 3) {
    return {};
  }

  int m = 0;
  vector<Point> res(n);

  sort(points.begin(), points.end());
  for (int i = 0; i < n; ++i) {
    if (m > 1 && (points[i] - res[m - 1]).cross(res[m - 1] - res[m - 2]) <= 0) {
      --m;
    }
    res[m++] = points[i];
  }
  for (int i = n - 1, j = m; i >= 0; --i) {
    if (m > j && (points[i] - res[m - 1]).cross(res[m - 1] - res[m - 2]) <= 0) {
      --m;
    }
    res[m++] = points[i];
  }
  res.resize(m);

  return res;
}

