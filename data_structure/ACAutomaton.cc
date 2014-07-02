#include <iostream>
#include <queue>

using namespace std;

#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 26;

class TrieNode {
public:
  TrieNode* child[MAXN];
  TrieNode* fail;
  int cnt;
  explicit TrieNode(): fail(nullptr), cnt(0) {
    for (int i = 0; i < MAXN; ++i) {
      child[i] = nullptr;
    }
  }
};

class ACAutomaton {
public:
  TrieNode* root;
  explicit ACAutomaton(): root() {
  }

  int get_index(char c) {
    return c - 'a';
  }

  void insert(const char* s) {
    TrieNode* cur = root;
    while (*s) {
      int ind = get_index(*s);
      if (! cur->child[ind]) {
        cur->child[ind] = new TrieNode();
      }
      cur = cur->child[ind];
      ++s;
    }
    ++cur->cnt;
  }

  void build(){
    queue<TrieNode*> que;

    for (int i = 0; i < MAXN; ++i) {
      if (root->child[i]) {
        root->child[i]->fail = root;
        que.push(root->child[i]);
      }
    }
    while (que.size()) {
      TrieNode* cur = que.front();
      que.pop();
      for (int i = 0; i < MAXN; ++i) {
        if (! cur->child[i]) {
          continue;
        }

        // Construction of fail pointer on non-root nodes
        TrieNode* p = cur->fail, *&v = cur->child[i]->fail;
        v = root;
        // Find the first node with chile[i], because we want the tail string
        // to match and as long as possible
        while (u != root && ! u->child[i]) {
          u = u->fail;
        }
        if (u->child[i]) {
          v = u->child[i];
        }
      }
    }
  }

};

int main() {
  return 0;
}
