// Find euler path or euler cycle in undierected graph, directed graph will 
// easier.
// This is a constructive algorithm
//
// Different from Fleury Algorithm, the core of the algorithm is keep the graph 
// connect when deleting a edge, unless there is no other choice. Easy to 
// understand, but hard coding.
class Fleury {
public:
  static const int MAXN = 205;
  static const int MAXE = 405;
  vector<pair<int, int> > ans;
  vector<pair<int, int> > e[MAXN];
  bool hash[MAXE];
  int d[MAXN];
  int b_euler; // -1: haven't check, 0: doesn't have euler path or cycle and 1 otherwise 
  int start;
  int n;
  int m;

  explicit Fleury(vector<pair<int, int> > e, int n) { // <u, v>
    this->n = n;
    this->m = (int)e.size();
    fill(d, d + n, 0);
    for (vector<pair<int, int> >::iterator i = e.begin(); i != e.end(); ++i) {
      int u = i->first, v = i->second;
      this->e[u].push_back(make_pair(v, i - e.begin()));
      this->e[v].push_back(make_pair(u, i - e.begin()));
      ++d[u];
      ++d[v];
    }
    fill(hash, hash + m, false);
    this->b_euler = -1;
    this->start = -1;
    ans.clear();
  }

  void _dfs(int u) {
    for (vector<pair<int, int> >::iterator i = e[u].begin(); i != e[u].end(); ++i) {
      if (!hash[i->second]) {
        hash[i->second] = true;
        _dfs(i->first);

        // Don't put this above _dfs() method
        ans.push_back(make_pair(i->first, u));
      }
    }
  }

  void _check(int u, set<int>& hash) {
    hash.insert(u);
    for (vector<pair<int, int> >::iterator i = e[u].begin(); i != e[u].end(); ++i) {
      if (!hash.count(i->first)) {
        _check(i->first, hash);
      }
    }
  }

  bool is_euler() {
    set<int> ver, hash;
    for (int i = 0; i < n; ++i) {
      if (d[i]) {
        ver.insert(i);
        start = i;
      }
    }
    _check(start, hash);
    // Check whether the graph connected
    if (hash.size() != ver.size()) {
      b_euler = false;
      return b_euler;
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (d[i] & 1) {
        ++cnt;
        start = i;
      }
    }
    b_euler = cnt == 0 || cnt == 2;
    return b_euler;
  }

  vector<pair<int, int> > euler_path() {
    if (b_euler == -1) {
      is_euler();
    }
    if (b_euler == 0) {
      return vector<pair<int, int> >();
    }

    assert(start != -1);
    _dfs(start);
    return ans;
  }
};
