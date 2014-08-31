// KMP

// pre[j] is the max value satisfying s[j-pre[j]+1..j] = s[1..pre[j]]
void findp(const char* s, vector<int>& pre) {
  int n = strlen(s), j = -1;
  pre.assign(n, 0);

  pre[0] = -1;
  for (int i = 1; i < n; ++i) {
    while (j != -1 && s[j + 1] != s[i]) {
      j = pre[j];
    }
    if (s[j + 1] == s[i]) {
      pre[i] = j + 1;
      ++j;
    } else {
      pre[i] = -1;
    }
  }
}

// haystack: original string, needle: pattern
// both start from index 0
char* kmp(char *haystack, char* needle) {
  char* s = haystack, *p = needle;
  int n = strlen(s);
  int m = strlen(p);
  vector<int> pre;

  findp(p, pre);
  int j = -1;
  for (int i = 0; i < n; ++i) {
    while (j != -1 && s[i] != p[j + 1]) {
      j = pre[j];
    }
    if (s[i] == p[j + 1]) {
      ++j;
    }
    if (j == m - 1) {
      // find the answer
      return haystack + (i - j);
    }
  }
  return nullptr;
}
