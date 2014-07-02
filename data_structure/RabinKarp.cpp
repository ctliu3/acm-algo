// Rabin-Karp algorithm - Las Vegas version, that is, always return a exact 
// answer.
// The complexity is approximate O(7N).

class RabinKarp {
  char* pat;
  long long phash;
  long long P; // a large prime, small enough to avoid overflow
  long long RM;
  int R; // radix
  int m; // length of pattern

  long long hash(char* key, int m) {
    long long h = 0;
    for (int i = 0; i < m; ++i) {
      h = (R * h + key[i]) % P;
    }
    return h;
  }

  // Monte Carlo version: always return true
  bool check(int i) {
    return i;
  }

  bool check(char* txt, int i) {
    for (int j = 0; j < m; ++j) {
      if (pat[j] != txt[i + j]) {
        return false;
      }
    }
    return true;
  }
public:

  explicit RabinKarp(char* pat, int m) {
    this->pat = pat;
    this->m = m;
    this->R = 256;
    this->P = 99999989;

    this->RM = 1;
    for (int i = 1; i <= m - 1; ++i) {
      RM = (R * RM) % P;
    }
    phash = hash(pat, m);
  }

  // return -1 if not find match else return the first matching position
  int search(char* txt, int n) {
    if (n < m) {
      return -1;
    }

    long long thash = hash(txt, m);
    // check for match at offset 0
    if (phash == thash && check(txt, 0)) {
      return 0;
    }

    for (int i = m; i < n; ++i) {
      thash = (thash + P - RM * txt[i - m] % P) % P;
      thash = (thash * R + txt[i]) % P;

      int offset = i - m + 1;
      if (phash == thash && check(txt, offset)) {
        return offset;
      }
    }

    return -1;
  }
};
