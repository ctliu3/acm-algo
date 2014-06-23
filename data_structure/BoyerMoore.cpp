// Basic implement of Boyer Moore algorithm,
// doesnt implement the strong good suffix rule

class BoyerMoore {
  char* pat;
  vector<int> right; // bad-character skip array
  int R; // radix
  int m; // length of the pattern

public:
  explicit BoyerMoore(char* pat, int m) {
    this->R = 256;
    this->m = m;
    this->pat = pat;

    // if right[] = -1, means the character in the txt does not come up
    // in the pat string
    this->right.assign(R, -1);
    for (int i = 0; i < m; ++i) {
      right[pat[i]] = i;
    }
  }

  int search(char* txt, int n) {
    int skip;
    for (int i = 0; i <= n - m; i += skip) {
      skip = 0;
      for (int j = m - 1; j >= 0; --j) {
        if (pat[j] != txt[i + j]) {
          // if not match, jump to the right most position
          // if right[] doesnt help, jump 1 character
          skip = max(1, j - right[txt[i + j]]);
        }
      }
      if (skip == 0) {
        return i;
      }
    }
    return -1; // not found
  }
};
