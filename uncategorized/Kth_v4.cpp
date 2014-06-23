// Kth (smallest) Number (say, Ascend order) - Partition Tree
// The time building segment tree is O(N*logN), each query cost O(logN), even
// in the worst case

struct Kth {
#define L(x) x << 1
#define R(x) x << 1 | 1
    struct Node {
        int l;
        int r;
    }a[MAXN * 3];
    static const int ROOT = 1;
    vector<int> sa; // sorted arrary 
    int val[20][MAXN];
    int ltn[20][MAXN]; // the no. of value assigned to the left subtree 

    void _build(int c, int l, int r, int d) { // d: depth of the seg tree
        a[c].l = l;
        a[c].r = r;

        if (l == r) {
            return ;
        }

        // all the processes are in the range [l, r]
        int mid = (l + r) >> 1;
        int idxl = l, idxr = mid + 1, same = 0, less = 0;
        for (int i = l; i <= r; ++i) {
            same += (val[d][i] == sa[mid]);
            less += (val[d][i] < sa[mid]);
        }

        int rest = mid - l + 1 - less;
        for (int i = l; i <= r; ++i) {
            ltn[d][i] = val[d][i] < sa[mid];
            if (i > l) {
                ltn[d][i] += ltn[d][i - 1];
            }

            if (val[d][i] < sa[mid]) {
                val[d + 1][idxl++] = val[d][i];
            } else if (val[d][i] > sa[mid]) {
                val[d + 1][idxr++] = val[d][i];
            } else { // val[d][i] == sa[mid]
                if (rest) {
                    val[d + 1][idxl++] = val[d][i];
                    --rest;
                    ++ltn[d][i];
                } else {
                    val[d + 1][idxr++] = val[d][i];
                }
            }
        }

        _build(L(c), l, mid, d + 1);
        _build(R(c), mid + 1, r, d + 1);
    }

    void init(int* arr, int n) {
        sa.assign(arr, arr + n);
        sort(sa.begin(), sa.end());
        for (int i = 0; i < n; ++i) {
            val[0][i] = arr[i];
        }
        _build(ROOT, 0, n - 1, 0);
    }

    int _query(int c, int l, int r, int d, int k) {
        if (l == r) {
            return val[d][l];
        }

        int lta; // the no. assigned to left substree in range [a[c].l, l - 1]
        int ltb; // the no. assigned to left substree in range [r + 1, a[c].r]
        int rta; // the no. assigned to right substree in range [a[c].l, l - 1]
        int rtb; // the no. assigned to right substree in range [r + 1, a[c].r]
        int m;   // the no. should assigned to left substree in range [l, r]

        lta = l == a[c].l ? 0 : ltn[d][l - 1];
        ltb = r == a[c].r ? 0 : ltn[d][a[c].r] - ltn[d][r];
        rta = l - a[c].l - lta;
        rtb = a[c].r - r - ltb;

        m = a[L(c)].r - a[L(c)].l + 1 - lta - ltb;
        int mid = (a[c].l + a[c].r) >> 1;

        // according to the m and k, we know what the k-th number loacted
        if (k <= m) {
            return _query(L(c), a[c].l + lta, mid - ltb, d + 1, k);
        } else {
            return _query(R(c), mid + 1 + rta, a[c].r - rtb, d + 1, k - m);
        }
    }

    int get_kth(int l, int r, int k) {
        return _query(ROOT, l, r, 0, k);
    }
};
