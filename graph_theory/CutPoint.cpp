// Cut Point and Cut Edge(Bridge)
//
// low(u) = Min {
// dfn(u)
// dfn(v) if dfn(v) < dfn(u) and v is not u's father
// low(v) if u is v's father
// }

struct CutPoint {
  int n;
  vector<int> e[MAXN];
  set<pair<int, int> > bridge;
  set<int> cp;
  int dfn[MAXN];
  int low[MAXN];

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; ++i) {
      e[i].clear();
    }
  }

  void add_edge(int u, int v) { // * 
    e[u].push_back(v);
    e[v].push_back(u);
  }

  void _dfs(int u, int f, const int root, int d) {
    dfn[u] = low[u] = d;
    int son = 0;

    for (vector<int>::iterator i = e[u].begin(); i != e[u].end(); ++i) {
      if (*i != f) {
        if (dfn[*i] != -1) {
          if (dfn[*i] < dfn[u]) {
            low[u] = min(low[u], dfn[*i]);
          }
        } else {
          _dfs(*i, u, root, d + 1);
          low[u] = min(low[u], low[*i]);
          ++son;

          if (u == root && son > 1 || u != root && low[*i] >= dfn[u]) { // >= 
            cp.insert(u);
          }
          if (low[*i] > dfn[u]) {
            bridge.insert(make_pair(min(*i, u), max(*i, u)));
          }
        }
      }
    }
  }

  void get_cp() {
    cp.clear();
    bridge.clear();
    fill(dfn, dfn + n, -1);

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        _dfs(i, -1, i, 0);
      }
    }
  }
};
