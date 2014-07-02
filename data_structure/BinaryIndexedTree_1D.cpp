// Binary Indexed Tree (BIT) - 1D ver
// Both modify and query's complexity is O(logN)

struct BinaryIndexedTree {
  int n;
  // c[i] = a[i - 2^k + 1] .. a[i], a is the origin array
  // k is the number of last zero of i in binary format, i.e. 6's k is 1
  // store in c[1..n]
  int c[MAXN];

  void init(int n) {
    this->n = n;
    fill(c + 1, c + n + 1, 0);
  }

  int _lowbit(int x) {
    return x & (x ^ (x - 1));
  }

  void modify(int pos, int delta) {
    while (pos <= n) {
      c[pos] += delta;
      pos += _lowbit(pos);
    }
  }

  // Return the sum of range [1..pos]
  int query(int pos) {
    int sum = 0;
    while (pos > 0) {
      sum += c[pos];
      pos -= _lowbit(pos);
    }
    return sum;
  }
};
