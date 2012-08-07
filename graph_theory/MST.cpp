// Minimum Spanning Tree (MST)

// Kruskal optimized with Disjoint
// Complexity is O(M*Log(M)), M is the number of edge
struct Edge {
    int u;
    int v;
    int w; // weight
    bool operator<(const Edge& lhs) const {
        return w < lhs.w;
    }
};

// return -1 if can't construct MST, otherwise the minimum cost
int MST(int n, vector<Edge>& e) {
    int sum = 0, cnt = 0;

    sort(e.begin(), e.end());
    ds.init(n); // define in ../data_structure/DisjointSet.cpp
    for (vector<Edge>::iterator itr = e.begin(); itr != e.end() && cnt != n - 1;
        ++itr) {
        if (ds.make_friend(itr->u, itr->v)) {
            sum += itr->w;
            ++cnt;
        }
    }
    return cnt == n - 1 ? sum : -1;
}
