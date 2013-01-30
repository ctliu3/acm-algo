// Matrix Multiplication

struct Matrix {
  int a[MAXN][MAXN];
  int n;

  Matrix() {
  }

  Matrix(int n) {
    memset(a, 0, sizeof(a));
    this->n = n;
  }

  void init(int a[][MAXN], int n) {
    this-> n = n;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        this->a[i][j] = a[i][j];
      }
    }
  }

  Matrix operator*(const Matrix& rhs) const {
    Matrix ret(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          ret.a[i][j] += (a[i][k] * rhs.a[k][j]) % MOD;
          ret.a[i][j] %= MOD;
        }
      }
    }
    return ret;
  }

  Matrix pow(int k) {
    Matrix ret(n), base = *this;
    for (int i = 0; i < n; ++i) {
      ret.a[i][i] = 1;
    }
    while (k) {
      if (k & 1) {
        ret = ret * base;
      }
      base = base * base;
      k >>= 1;
    }
    return ret;
  }
};
