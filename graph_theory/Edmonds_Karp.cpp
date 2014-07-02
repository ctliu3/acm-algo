// Maximum Flow Algorithm (Kdmonds Karp) 
// Complexity is O(VE^2)
struct Edge {
  int v;
  int c;
};

struct Kdmonds_Karp {
  int n, m, source, sink;
  vector<int> e[MAXN];
  Edge edge[MAXE * 2];

  void init(int n, int source, int sink) {
    this->n = n;
    this->m = 0; // edge index 
    this->source = source;
    this->sink = sink;
    for (int i = 0; i < n; ++i) {
      e[i].clear();
    }
  }

  void add_edge(int a, int b, int c) { // one-way edge
    //printf("add edge: (%d, %d) -> %d\n", a, b, c);
    edge[m].v = b;
    edge[m].c = c;
    e[a].push_back(m++);
    edge[m].v = a;
    edge[m].c = 0;
    e[b].push_back(m++);
  }

  int d[MAXN];
  int pv[MAXN]; // note the path, path vertex
  int pe[MAXN]; // path edge index

  bool _bfs() { // find a augument path 
    queue<int> q;
    fill(d, d + n, -1);

    q.push(source);
    d[source] = 0;
    while (!q.empty()) {
      int s = q.front();
      for (size_t i = 0; i < e[s].size(); ++i) {
        int id = e[s][i], to = edge[id].v;
        if (d[to] == -1 && edge[id].c > 0) {
          d[to] = d[s] + 1;
          pv[to] = s;
          pe[to] = id;
          if (to == sink) {
            return true;
          }
          q.push(to);
        }
      }
      q.pop();
    }
    return false;
  }

  int max_flow() {
    int flow = 0;
    while (_bfs()) {
      int aug_flow = INF;
      for (int i = sink; i != source; i = pv[i]) {
        aug_flow = min(aug_flow, edge[pe[i]].c);
      }
      assert(aug_flow != INF);
      for (int i = sink; i != source; i = pv[i]) {
        edge[pe[i]].c -= aug_flow;
        edge[pe[i] ^ 1].c += aug_flow; // * 
      }
      flow += aug_flow;
    }
    return flow;
  }
};
