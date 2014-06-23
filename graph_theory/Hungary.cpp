struct Hungary {
    int n; // left 
    vector<int> e[MAXN]; // left
    
    // n: left [0, n - 1], m: right [0, m - 1]
    void init(int n, int m) {
        this->n = n;
        for (int i = 0; i < n; ++i) {
            e[i].clear();
        }
        match.resize(m); // *
        used.resize(m); // * 
    }
    
    void add_egdg(int a, int b) {
        //printf("%d -> %d\n", a, b);
        e[a].push_back(b);
    }

    vector<int> match; // right, match[u] = v, u is right, v is left
    vector<int> used; // right 

    bool _aug(int u) {
        for (vector<int>::iterator itr = e[u].begin(); itr != e[u].end(); ++itr) {
            if (!used[*itr]) {
                used[*itr] = true;
                if (match[*itr] == -1 || _aug(match[*itr])) {
                    match[*itr] = u;
                    return true;
                }
            }
        }
        return false;
    }

    int max_match() {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            fill(used.begin(), used.end(), false);
            res += _aug(i);
        }
        return res;
    }
};
