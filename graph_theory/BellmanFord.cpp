// Bellman Ford Short Path
// Complexity is O(N*M), M is the number of edge

struct Edge {
    int u;
    int v;
    int w;
    explicit Edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {
    }
};

struct BellmanFord {
    int n;
    int m;
    Edge e[MAXE];

    void init(int n) {
        this->n = n;
        this->m = 0;
    }

    void add_edge(int a, int b, int c) { // one-way path
        e[m++] = Edge(a, b, c);
    }

    int dis[MAXN];

    // return true if theere is a negative cycle
    bool sp(int s = 0) { // start point
        fill(dis, dis + n, INF);
        dis[s] = 0;

        for (int j = 0; j < n - 1; ++j) { // n - 1 times
            bool update = false;
            for (int i = 0; i < m; ++i) {
                int u = e[i].u;
                int v = e[i].v;
                int w = e[i].w;
                if (dis[u] + w < dis[v]) { // relaxing
                    dis[v] = dis[u] + w;
                    update = true;
                }
            }
            if (!update) {
                break;
            }
        }
        for (int i = 0; i < m; ++i) { 
            if (dis[e[i].u] + e[i].w < dis[e[i].v]) {
                return true; // a negative cycle
            }
        }
        return false;
    }
};
