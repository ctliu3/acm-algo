// KMP

// a, b: index from 1..n (1..m)
bool kmp(char a[], char b[], int p[], int n, int m) {
  int j = 0;
  for (int i = 1; i <= n; ++i) {
    while (j > 0 && a[i] != b[j + 1]) {
      j = p[j];
    }
    if (a[i] == b[j + 1]) { // a[i-j+1..i] = b[1..j]
      ++j;
    }
    if (j == m) { // get match
      return true;
      // j = p[j]; // if want to get the next match
    }
  }
  return false;
}

// p[j] is the max value satisfying b[j-p[j]+1..j] = b[1..p[j]]
// b: pattern, p: array next, n: size
void getp(char b[], int p[], int n) {
  p[1] = 0;
  int j = 0;
  for (int i = 2; i <= n; ++i) {
    while (j > 0 && b[i] != b[j + 1]) {
      j = p[j];
    }
    if (b[i] == b[j + 1]) {
      ++j;
    }
    p[i] = j;
  }
}
