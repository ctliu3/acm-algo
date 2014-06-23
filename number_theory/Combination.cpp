// Pascal's Triangle
// C(N, K) = C(N - 1, K - 1) + (N - 1, K)
int C[MAXN][MAXN];

void pascal_triangle(int n, int mod = 1) {
    for (int i = 0; i <= n; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
            assert(C[i][j] >= 0);
        }
    }
}
