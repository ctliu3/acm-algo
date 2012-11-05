// Merge Sort (Ascending order)
// Time complexity is O(N*2logN), space complexity is O(N)

template<typename T>
void _merge(int left, int right, vector<T>& arr) {
    int mid = (left + right) >> 1;
    int l = left, r = mid + 1, n = 0;

    vector<T> ta(right - left + 1);
    while (l <= mid && r <= right) {
        ta[n++] = arr[l] < arr[r] ? arr[l++] : arr[r++];
    }
    while (l <= mid) {
        ta[n++] = arr[l++];
    }
    while (r <= right) {
        ta[n++] = arr[r++];
    }
    for (int i = 0; i < n; ++i) {
        arr[left + i] = ta[i];
    }
}

template<typename T>
void _merge_sort(int left, int right, vector<T>& arr) {
    if (left >= right) {
        return ;
    }
    int mid = (left + right) >> 1;
    _merge_sort(left, mid, arr); // divide
    _merge_sort(mid + 1, right, arr);
    _merge(left, right, arr); // conque
}

template<typename T>
void merge_sort(vector<T>& arr) {
    _merge_sort(0, arr.size() - 1, arr);
}
