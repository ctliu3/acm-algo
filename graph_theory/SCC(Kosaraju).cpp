// Strongly Connected Components (SCC) - implement with Kosaraju algo
// Complexity is O(N+M)

struct Kosaraju {
    int n;
    int sccn;
    vector<int> e[MAXN], re[MAXN], scce[MAXN]; // *
    vector<int> ts; // timestamp
    int sccid[MAXN]; // sccid[i] means which scc id i belong to

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; ++i) {
            e[i].clear();
            re[i].clear();
        }
    }

    void add_edge(int u, int v) {
        e[u].push_back(v);
        re[v].push_back(u);
    }

    bool vis[MAXN]; // *

    void _dfs(int u) {
        vis[u] = true;
        for (vector<int>::iterator itr = e[u].begin(); itr != e[u].end(); ++itr) {
            if (!vis[*itr]) {
                _dfs(*itr);
            }
        }
        ts.push_back(u); // * 
    }

    void _dfs(int u, int id) {
        vis[u] = true;
        sccid[u] = id;
        for (vector<int>::iterator itr = re[u].begin(); itr != re[u].end(); ++itr) {
            if (!vis[*itr]) {
                _dfs(*itr, id);
            } 
        }
    }

    void get_sccg() {
        set<pair<int, int> > es;
        for (int i = 0; i < sccn; ++i) {
            scce[i].clear();
        }
        for (int i = 0; i < n; ++i) {
            for (vector<int>::iterator j = e[i].begin(); j != e[i].end(); ++j) {
                int u = sccid[i];
                int v = sccid[*j];
                if (u != v && !es.count(make_pair(u, v))) {
                    es.insert(make_pair(u, v));
                    scce[u].push_back(v);
                }
            }
        }
    }

    int scc() {
        fill(vis, vis + n, false);
        ts.clear();
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                _dfs(i);
            }
        }

        sccn = 0;
        fill(vis, vis + n, false);
        for (vector<int>::reverse_iterator rit = ts.rbegin(); rit != ts.rend(); 
            ++rit) {
            if (!vis[*rit]) {
                _dfs(*rit, sccn++);
            }
        }
        return sccn;
    }
};
