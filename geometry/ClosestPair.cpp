// Closest Pair - Divide and Conquer
// Complexity is O(N*logN)

struct Point {
    double x;
    double y;
    explicit Point(double x, double y): x(x), y(y) {
    }
    bool operator<(const struct Point rhs) const {
        return x < rhs.x;
    }
};

inline double dis(struct Point lhs, struct Point rhs) {
    return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y);
}

struct ClosestPair {
    int n;
    vector<Point> p;
    static const int BOUND = 8;

    void init(int n) {
        this-> n = n;
        p.clear();
    }

    void add_point(double x, double y) {
        p.push_back(Point(x, y));
    }

    double _find_pair(int left, int right) {
        if (right - left < BOUND) {
            double td = 1E20;
            for (int i = left; i < right; ++i) {
                for (int j = i + 1; j <= right; ++j) {
                    td = min(td, dis(p[i], p[j]));
                }
            }
            return td;
        }

        int mid = (left + right) >> 1;
        double ldis = _find_pair(left, mid);
        double rdis = _find_pair(mid, right);

        double bst = min(ldis, rdis);
        vector<pair<double, double> > lp, rp;
        int lc = mid - 1, rc = mid + 1;
        while (lc >= left && p[mid].x - p[lc].x < bst) {
            lp.push_back(make_pair(p[lc].y, p[lc].x));
            --lc;

        }
        while (rc <= right && p[rc].x - p[mid].x < bst) {
            rp.push_back(make_pair(p[rc].y, p[rc].x));
            ++rc;
        }

        sort(lp.begin(), lp.end());
        sort(rp.begin(), rp.end());

        int k = 0;
        for (size_t i = 0; i < lp.size(); ++i) {
            for (size_t j = k; j < rp.size(); ++j) {
                if (fabs(rp[j].second - lp[i].second) >= bst) {
                    continue;
                }
                if (rp[j].first - lp[i].first >= bst) { // *
                    break;
                }
                if (lp[i].first - rp[j].first >= bst) { // *
                    k = j;
                    continue;
                }
                bst = min(bst, dis(Point(lp[i].second, lp[i].first), 
                        Point(rp[j].second, rp[j].first)));
            }
        }
        return bst;
    }
    
    double closest_dis() {
        sort(p.begin(), p.end());
        double dis = _find_pair(0, n - 1);
        return sqrt(dis) / 2;
    }
};
