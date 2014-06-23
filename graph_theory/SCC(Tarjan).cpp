// Strongly Connected Components (SCC) - implement with Tarjan algo
// Complexity is O(N+M)

struct Tarjan {
    int n;
    int sccn;
    vector<int> e[MAXN], scce[MAXN];
    bool flag[MAXN];
    int dfn[MAXN], low[MAXN];
    int sccid[MAXN];
    int stack[MAXN];

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; ++i) {
            e[i].clear();
        }
    }

    void add_edge(int u, int v) {
        e[u].push_back(v);
    }

    int top; // 

    void _dfs(int u, int d) {
        low[u] = dfn[u] = d;
        flag[u] = true;
        stack[++top] = u;

        for (vector<int>::iterator i = e[u].begin(); i != e[u].end(); ++i) {
            if (dfn[*i] == -1) {
                _dfs(*i, d + 1);
                low[u] = min(low[u], low[*i]);
            } else if (flag[*i]) {
                low[u] = min(low[u], dfn[*i]); // *
            }
        }

        if (low[u] == dfn[u]) {
            int j;
            do {
                j = stack[top--];
                sccid[j] = sccn;
                flag[j] = false;
            } while (j != u);
            ++sccn;
        }
    }

    int scc() {
        fill(flag, flag + n, false);
        fill(dfn, dfn + n, -1);
        sccn = 0;
        for (int i = 0; i < n; ++i) {
            top = -1;
            if (dfn[i] == -1) {
                _dfs(i, 0);
            }
        }
        return sccn;
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
};
