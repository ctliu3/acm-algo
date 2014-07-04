#include <iostream>
#include <vector>

using namespace std;

class SegNode {
public:
  int left, right;
  int val;
  explicit SegNode(): val(0) {
  }
  int mid() {
    return left + (right - left) / 2;
  }
};

class SegTree {
public:
  explicit SegTree(vector<int>& v) {
    root = 1; // the index starts from 1
    nodes.resize(v.size() * 4);
    build(v, root, 1, v.size());
  }

  // udpate the single point
  void insert(int idx, int pos, int val) {
    nodes[idx].val += val;
    if (nodes[idx].left == pos && nodes[idx].right == pos) {
      return ;
    }
    int mid = nodes[idx].mid();
    if (pos <= mid) {
      insert(L(idx), pos, val);
    } else if (pos >= mid + 1) {
      insert(R(idx), pos, val);
    }
  }

  // return sum in the range of [left, right]
  int query(int idx, int left, int right) {
    if (nodes[idx].left == left && nodes[idx].right == right) {
      return nodes[idx].val;
    }
    int mid = nodes[idx].mid();
    if (right <= mid) {
      return query(L(idx), left, right);
    } else if (left >= mid + 1) {
      return query(R(idx), left, right);
    } else {
      return query(L(idx), left, mid) + query(R(idx), mid + 1, right);
    }
  }

private:
  void build(vector<int>& v, int idx, int left, int right) {
    SegNode& cur = nodes[idx];
    cur.left = left, cur.right = right;
    if (left == right) {
      cur.val = v[left - 1];
      return ;
    }
    int mid = cur.mid();
    build(v, L(idx), left, mid);
    build(v, R(idx), mid + 1, right);
    cur.val = nodes[L(idx)].val + nodes[R(idx)].val;
  }

  int L(int x) {
    return x << 1;
  }

  int R(int x) {
    return (x << 1) | 1;
  }

  vector<SegNode> nodes;
  int root;
};
