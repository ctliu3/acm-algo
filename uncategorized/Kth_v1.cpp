// Kth (smallest) Number (say, Ascend order)
// Time Complexity is O(N*logN), but the worest case is O(N*N)
// And how the deal with continuous query with range [L, R] and K?

struct Kth {
    int n;
    int k;
    vector<int> arr;

    void init(vector<int> a, int k) {
        this->n = (int)a.size();
        this->k = k;
        arr.assign(a.begin(), a.end());
    }

    void _swap(int& a, int& b) {
        a ^= b ^= a ^= b;
    }

    int _partition(int left, int right, int pivot) {
        // It may important that you should switch the number in pivot with the 
        // last number, say, the end one. We do this in case that if you meet
        // the condition `m == k` in get_kth(), you can ensure that the last one
        // in the arr[left..right] is the value you want(the largest one)
        _swap(arr[pivot], arr[right]);
        int t = arr[right], c = left;
        for (int i = left; i <= right; ++i) {
            if (arr[i] <= t) { // *
                _swap(arr[i], arr[c]);
                ++c;
            }
        }
        return c - 1;
    }

    int get_kth() {
        int left = 0, right = n - 1;
        int t = 1;
        while (right - left >= 1) {
            // You can also change the third parameter `left` with any index in
            // range [left, right], such as `left + rand() % (right - left + 1)`
            int idx = _partition(left, right, left);
            int m = idx - left + 1;
            if (m == k) { // *
                return arr[idx];
            } else if (m < k) { // *
                k -= m;
                left = idx + 1;
            } else {
                right = idx - 1; // *
            }
        }
        assert(left == right);
        return arr[left]; 
    }
};
