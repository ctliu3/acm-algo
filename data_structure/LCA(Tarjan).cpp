// Lowest Common Ancestors (LCA)
// DisjointSet struct define in ../data_structure/DisjointSet.cpp

bool used[MAXN];
int dis[MAXN]; // distance from root to node i
int color[MAXN]; // color diff connected component
vector<int> query[MAXN];
vector<int> e[MAXN]; // vector<pair<int, int> > if needed

// color the connected component
void dfs(int u, int id) {
  color[u] = id;
  for (vector<int>::iterator itr = e[u].begin(); itr != e[u].end(); ++itr) {
    if (color[*itr] == -1) {
      dfs(*itr, id);
    }
  }
}

void _lca(int u) {
  for (vector<int>::iterator itr = e[u].begin(); itr != e[u].end(); ++itr) {
    if (!used[*itr]) {
      dis[*itr] = dis[u] + 1; // 1 is weight of edge
      _lca(*itr);
      // Here, i do not use ancestor array, instead, i always make the u
      // the parent of *itr, it's important.
      // If you cannot promise this, use ancestor array
      ds.make_friend(u, *itr);
    }
  }
  used[u] = true; // *
  for (vector<int>::iterator itr = query[u].begin(); itr != query[u].end(); 
    ++itr) {
    if (used[*itr] && color[u] == color[*itr]) {
      // ds.get_father(*itr) is the ancestor of the pair <u, *itr>
      // lca distance is dis[u] + dis[*itr] - 2 * dis[ds.get_father(*itr)]
    }
  }
}

// main
void lca(int n) {
  vector<int> in(n, 0);

  fill(color, color + n, -1);
  // Get the roots of the forest, if in[i] = 0, then i is the root
  for (int i = 0; i < n; ++i) {
    for (vector<int>::iterator j = e[i].begin(); j != e[i].end(); ++j) {
      ++in[*j];
    }
  }
  int id = 0;
  // Handle diff connected component
  for (int i = 0; i < n; ++i) {
    if (!in[i] && color[i] == -1) {
      dfs(i, id++);
    }
  }

  fill(used, used + n, false);
  fill(dis, dis + n, 0);
  ds.init(n); // * DisjointSet struct
  for (int i = 0; i < n; ++i) {
    if (!in[i] && !used[i]) {
      _lca(i);
    }
  }
}
