// Topo Sort, simple BFS
// Complexity is O(VE)
vector<int> e[MAXN];
vector<int> ord; // note the path 
int in[MAXN]; // if (_, a) exists, then ++in[a]

bool topo_sort(int n) {
    queue<int> q;

    ord.clear();
    for (int i = 0; i < n;++i) {
        if (!in[i]) { 
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (vector<int>::iterator itr = e[u].begin(); itr != e[u].end(); ++itr) {
            if (!(--in[*itr])) {
                q.push(*itr);
            }
        }
    }
    return ord.size() == n;
}
