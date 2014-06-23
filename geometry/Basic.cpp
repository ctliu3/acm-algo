
struct Point {
  double x, y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }
  double length() const { return hypot(x, y); }
  double polar() const { return atan2(y, x); }
  Point normal() const { return Point(y, -x); }
  Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
  Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
  Point operator*(const double o) const { return Point(x * o, y * o); }
  double operator*(const Point& o) const { return x * o.y - y * o.x; }
};
