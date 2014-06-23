// Lowest Common Ancestors (LCA), online query
// Query complexity is O(logN)

const int MAXB = 20;
vector<int> e[MAXN];
int p[MAXN][MAXB]; // ST
int d[MAXN]; // deep of node i

void dfs(int u, int f) { // f is the father of u
    p[u][0] = f;
    for (int i = 1; i < MAXB; ++i) {
        p[u][i] = p[p[u][i - 1]][i - 1];
    }
    for (auto& v: e[u]) {
        if (v == f) {
            continue;
        }
        d[v] = d[u] + 1;
        dfs(v, u);
    }
}

int go_up(int v, int d) {
    for (int i = 0; i < MAXB; ++i) {
        if (d & (1 << i)) {
            v = p[v][i];
        }
    }
    return v;
}

int lca(int a, int b) {
    if (d[a] > d[b]) {
        swap(a, b);
    }
    // let a, b be the same deep(level)
    b = go_up(b, d[b] - d[a]);
    if (a == b) {
        return a;
    }
    for (int i = MAXB - 1; i >= 0; --i) { // *
        if (p[a][i] != p[b][i]) {
            a = p[a][i];
            b = p[b][i];
        }
    }
    return p[a][0];
}
