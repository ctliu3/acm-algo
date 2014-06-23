#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <queue>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  explicit TreeNode(int val = 0): val(val), left(NULL), right(NULL) {
  }
};

TreeNode* build(string s) {
  for (auto& c : s) {
    if (c == ',' || c == '{' || c == '}') {
      c = ' ';
    }
  }

  vector<TreeNode* > tree;
  istringstream sin(s);
  string sub;
  while (sin >> sub) {
    tree.push_back(sub == "#" ? NULL : new TreeNode(atoi(sub.c_str())));
  }

  if (tree.size() == 0) {
    return NULL;
  }

  int n = (int)tree.size();
  for (int i = 0; i < n; ++i) {
    int l = (i + 1) * 2 - 1, r = l + 1;
    if (l < n && tree[l]) {
      tree[i]->left = tree[l];
    }
    if (r < n && tree[r]) {
      tree[i]->right = tree[r];
    }
  }

  return tree[0];
}

void level_order(TreeNode* root) {
  fprintf(stderr, "Level order: \n");
  queue<TreeNode* > q;

  q.push(root);
  while (!q.empty() && root) {
    TreeNode* cur = q.front();
    q.pop();
    fprintf(stderr, "%d ", cur->val);
    if (cur->left) {
      q.push(cur->left);
    }
    if (cur->right) {
      q.push(cur->right);
    }
  }
  fprintf(stderr, "\n\n");
}

void preorder(TreeNode* root) {
  fprintf(stderr, "Preorder: \n");
  stack<TreeNode*> stk;

  stk.push(root);
  while (!stk.empty() && root) {
    TreeNode* top = stk.top();
    stk.pop();
    fprintf(stderr, "%d ", top->val);
    if (top->right) {
      stk.push(top->right);
    }
    if (top->left) {
      stk.push(top->left);
    }
  }
  fprintf(stderr, "\n\n");
}

void inorder(TreeNode* root) {
  fprintf(stderr, "Inorder: \n");
  stack<TreeNode*> stk;
  TreeNode* cur = root;

  while (!stk.empty() || cur) {
    while (cur) {
      stk.push(cur);
      cur = cur->left;
    }
    if (!stk.empty()) {
      cur = stk.top();
      stk.pop();
      fprintf(stderr, "%d ", cur->val);
      cur = cur->right;
    }
  }
  fprintf(stderr, "\n\n");
}

void postorder(TreeNode* root) {
  fprintf(stderr, "Postorder: \n");
  if (!root) {
    return ;
  }

  stack<TreeNode*> stk;
  TreeNode* cur = root, *pre = NULL;
  do {
    while (cur) {
      stk.push(cur);
      cur = cur->left;
    }

    cur = stk.top();
    if (!cur->right || cur->right == pre) {
      fprintf(stderr, "%d ", cur->val);
      stk.pop();
      pre = cur;
      cur = NULL;
    } else {
      cur = cur->right;
    }

  } while (!stk.empty());

  fprintf(stderr, "\n\n");
}

int main() {
  string stree = "{1,2,3,4,5,#,6,7}";
  TreeNode* root = build(stree);

  level_order(root);
  preorder(root);
  inorder(root);
  postorder(root);
  return 0;
}
