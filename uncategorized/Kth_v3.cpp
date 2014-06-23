// Kth (smallest) Number (say, Ascend order) - Merging Tree
// The time building segment tree is O(N*logN), each query cost O(logN*logN*logN)
// I should say, the two times binary search is not easy to code right, 
// be careful:-)

struct Kth {
#define L(x) x << 1
#define R(x) x << 1 | 1
    struct Node {
        int l;
        int r;
    }a[MAXN * 3];
    static const int ROOT = 1;
    vector<int> ra; // raw array
    int val[20][MAXN];
    int n;

    void _build(int c, int l, int r, int d) { // d: depth
        a[c].l = l;
        a[c].r = r;
        if (l == r) {
            val[d][l] = ra[l];
            return ;
        }
        int mid = (l + r) >> 1;
        _build(L(c), l, mid, d + 1);
        _build(R(c), mid + 1, r, d + 1);

        // Similar to merge sort.
        int i = l, j = mid + 1, k = l;
        while (i <= mid && j <= r) {
            if (val[d + 1][i] < val[d + 1][j]) {
                val[d][k++] = val[d + 1][i++];
            } else {
                val[d][k++] = val[d + 1][j++];
            }
        }
        while (i <= mid) {
            val[d][k++] = val[d + 1][i++];
        }
        while (j <= r) {
            val[d][k++] = val[d + 1][j++];
        }
    }

    void init(int* arr, int n) {
        this->n = n;
        ra.assign(arr, arr + n);
        _build(ROOT, 0, n - 1, 0);
    }

    int _bsearch(int l, int r, int d, int key) {
        if (key < val[d][l]) {
            return 0;
        }
        if (key > val[d][r]) {
            return r - l + 1;
        }
        // Second binary search, if the sub query range is exact cover current 
        // subtree range, then do this.
        int lo = l, hi = r;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (val[d][mid] < key) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return val[d][lo] <= key ? lo - l + 1 : lo - l;
    }

    // Return the rank of val(key) the range [l, r]
    int _query(int c, int l, int r, int d, int key) {
        if (a[c].l == l && a[c].r == r) {
            return _bsearch(l, r, d, key);
        }
        int mid = (a[c].l + a[c].r) >> 1;
        if (r <= mid) {
            return _query(L(c), l, r, d + 1, key);
        } else if (l >= mid + 1) {
            return _query(R(c), l, r, d + 1, key);
        } else {
            return _query(L(c), l, mid, d + 1, key) 
                + _query(R(c), mid + 1, r, d + 1, key);
        }
    }

    int get_kth(int l, int r, int k) {
        // First binary search, do this in the range [0, n - 1]
        int lo = 0, hi = this->n - 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            int p = _query(ROOT, l, r, 0, val[0][mid]);
            if (p < k) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return val[0][lo];
    }
};
