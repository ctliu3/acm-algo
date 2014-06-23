// Implementation of permutation, the permutation in the res is unique,
// that it, [1, 1, 3] will return [1, 1, 3], [1, 3, 1] and [3, 1, 1],
// not 3!.

void reverse(vector<int>& num, int i, int j) {
  while (i < j) {
    swap(num[i++], num[j--]);
  }
}

void next_permutation(vector<int> &num) {
  int n = (int)num.size();
  if (n < 2) {
    return ;
  }

  int i = n - 2; 
  while (i >= 0 && num[i] >= num[i + 1]) {
    --i;
  }
  if (i == -1) {
    reverse(num, 0, n - 1);
    return ;
  }
  int j = n - 1;
  while (j > i && num[j] <= num[i]) {
    --j;
  }
  swap(num[i], num[j]);
  reverse(num, i + 1, n - 1);
}

int main() {
  vector<int> a = {1, 1, 3};
  vector<vector<int>> res;

  sort(a.begin(), a.end());
  do {
    res.push_back(a);
    next_permutation(a);
  } while (!equal(res[0].begin(), res[0].end(), a.begin()));

  for (auto& vi : res) {
    for (auto& a : vi) {
      cout << a << ' ';
    }
    cout << endl;
  }

  return 0;
}
