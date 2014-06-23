// Ranage Maximum(Minimum) Query, RMQ
// Preprocessing's complexity is O(N*logN), query is O(1), <O(N*logN), O(1)> 
// Following is get max value in range [l, h], almost the same for min value

const int MAXM = 20; // MAXM = _log2(MAXN)

int A[MAXN]; // store in [0..n - 1] 
int M[MAXN][MAXM]; // sparse table

int _log2(int a) {
    int k = 0;
    while ((1 << k) <= a) {
        ++k;
    }
    return k - 1;
}

void init_rmq(int n) {
    for (int i = 0; i < n; ++i) {
        M[i][0] = i;
    }
    for (int j = 1; (1 << j) <= n; ++j) { // = 
        for (int i = 0; i + (1 << j) <= n; ++i) { // =
            // M[i][j] = M[i][j - 1], A[M[i][j - 1]] > A[M[i + (1 << (j - 1))]][j - 1]
            // M[i][j] = M[i + (1 << (j - 1))][j - 1], otherwise
            int p = M[i][j - 1];
            int q = M[i + (1 << (j - 1))][j - 1];
            M[i][j] = A[p] < A[q] ? q : p;
        }
    }
}

// Return the maximum value in array A's index
int rmq_max(int l, int h) {
    if (l > h) {
        swap(l, h);
    }
    int k = _log2(h - l + 1);
    // Max value = max(A[M[l][k]], A[M[h - (1 << k) + 1][k]]);
    int p = M[l][k];
    int q = M[h - (1 << k) + 1][k];
    return A[p] > A[q] ? p : q;
}
