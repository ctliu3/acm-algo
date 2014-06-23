// Heap Sort (Ascending order)
// Time complexity is O(NlogN), space complexity is O(1)

// Update the heap the maintain the heap property (max-heap):
// for each node i, arr[i] > arr[left] && arr[i] > arr[right]
template<typename T>
void _modify(vector<T>& arr, int cur, int sz) {
    int l = cur * 2 + 1, r = l + 1, best = cur;
    if (l < sz && arr[cur] < arr[l]) {
        best = l;
    }
    if (r < sz && arr[best] < arr[r]) {
        best = r;
    }
    if (best != cur) {
        swap(arr[cur], arr[best]);
        _modify(arr, best, sz);
    }
}

template<typename T>
void heap_sort(vector<T>& arr) {
    for (int i = arr.size() / 2; i >= 0; --i) { // not size_t 
        _modify(arr, i, arr.size());
    }
    for (int i = arr.size() - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        _modify(arr, 0, i);
    }
}
