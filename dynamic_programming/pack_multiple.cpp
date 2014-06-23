#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int INF = -1e8;

// N is the total size of the pack
int pack_multiple(vector<int>& weight, vector<int>& value, int N) {
  assert(weight.size() == value.size());

  int n = weight.size();
 // whether the pack should be fully filled? two type of initialization
  vector<int> pack(N + 1, INF);

  pack[0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = weight[i]; j <= N; ++j) {
      pack[j] = max(pack[j], pack[j - weight[i]] + value[i]);
    }
  }

  return pack[N];
}

int main() {
  vector<int> weight = {4, 4, 4};
  vector<int> value = {10, 90, 12};
  int res = pack_complete(weight, value, 8);
  cout << res << endl;

  return 0;
}
