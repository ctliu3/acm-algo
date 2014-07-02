// Disjoint Set
struct DisjointSet {
  int n;
  int p[MAXN];

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; ++i) {
      p[i] = i;
    }
  }
  int get_father(int u) { // *
    if (p[u] != u) {
      p[u] = get_father(p[u]);
    }
    return p[u]; // *
  }
  bool is_friend(int a, int b) {
    return get_father(a) == get_father(b);
  }
  // return false if <a, b> are already in the same set
  bool make_friend(int a, int b) { // a is parent of set b!!!
    a = get_father(a);
    b = get_father(b);
    if (a == b) {
      return false;
    }
    p[b] = a;
    return true;
  }
};
