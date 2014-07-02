// Minimum Cost Maximum Flow

struct Edge {
  int v;
  int r; // #flow 
  int c; // cost 
  int b; // index of the reverse edge
  explicit Edge(int v, int r, int c, int b): v(v), r(r), c(c), b(b) {
  }
};

struct MinCostMaxFlow {
  int n, source, sink;
  vector<Edge> e[MAXN];

  void init(int n, int source, int sink) {
    this->n = n;
    this->source = source;
    this->sink = sink;
    for (int i = 0; i < n; ++i) {
      e[i].clear();
    }
  }

  void add_edge(int a, int b, int f, int c) { // f: #flow, c: cost 
    e[a].push_back(Edge(b, f, c, e[b].size()));
    e[b].push_back(Edge(a, 0, -c, e[a].size() - 1));
  }

  int pv[MAXN]; // note the path 
  int pe[MAXN]; // note the path 
  int cost[MAXN]; // cost[i]: the cost from source to vertex i
  bool onqueue[MAXN];

  bool _spfa() {
    queue<int> q;

    fill(cost, cost + n, numeric_limits<int>::max());
    fill(onqueue, onqueue + n, false);
    cost[source] = 0;

    q.push(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      onqueue[u] = false;

      for (vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
        int v = it->v;
        int c = it->c;
        // maybe overflow, fix it next time
        if (it->r && c < cost[v] - cost[u]) { // it->r always >= 0
          cost[v] = cost[u] + c;
          pv[v] = u;
          pe[v] = e[v][it->b].b;
          if (!onqueue[v]) {
            onqueue[v] = true;
            q.push(v);
          }
        }
      }
    }
    return cost[sink] != numeric_limits<int>::max();
  }

  pair<int, int> mincost() {
    int mf = 0, mc = 0;
    while (_spfa()) {
      int aug = numeric_limits<int>::max();
      for (int i = sink; i != source; i = pv[i]) {
        aug = min(aug, e[pv[i]][pe[i]].r);
      }
      mf += aug;
      mc += aug * cost[sink];
      for (int i = sink; i != source; i = pv[i]) {
        Edge* e1 = &e[pv[i]][pe[i]];
        e1->r -= aug; // * 
        Edge* e2 = &e[e1->v][e1->b];
        e2->r += aug; // * 
      }
    }
    return make_pair(mc, mf);
  }
};
