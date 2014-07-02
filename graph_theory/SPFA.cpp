// SPFA, a optimal version of Bellman Ford
// Note: If you want to use SPFA to check whether there is a cycle, put all the
//       nodes to queue to handle the case the graph is not connective

struct Edge {
  int v;
  int w;
};

struct SPFA {
  int n;
  int m;
  vector<int> e[MAXN];
  Edge edge[MAXE];

  void init(int n) {
    this->n = n;
    this->m = 0;
    for (int i = 0; i < n; ++i) {
      e[i].clear();
    }
  }

  void add_edge(int a, int b, int c) { // one-way path
    edge[m].v = b;
    edge[m].w = c;
    e[a].push_back(m++);
  }

  int dis[MAXN];
  int cnt[MAXN];
  bool onqueue[MAXN];

  // return true if theere is a negative cycle
  bool sp(int s = 0) { // start point
    queue<int> q;
    fill(dis, dis + n, INF);
    fill(cnt, cnt + n, 0);

    q.push(s);
    dis[s] = 0;
    cnt[s] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      onqueue[u] = false;

      for (vector<int>::iterator itr = e[u].begin(); itr != e[u].end(); ++itr) {
        int v = edge[*itr].v;
        int w = edge[*itr].w;
        if (dis[u] + w < dis[v]) {
          dis[v] = dis[u] + w;
          if (!onqueue[v]) {
            onqueue[v] = true;
            ++cnt[v];
            if (cnt[v] > n) {
              return true;
            }
            q.push(v);
          }
        }
      }
    }
    return false;
  }
};
