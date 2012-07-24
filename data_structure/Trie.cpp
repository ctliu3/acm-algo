// Trie
// Following code counts the number of the same prefix string
const int CN = 26; // *

struct Node {
    Node* next[CN];
    int cnt;

    Node(): cnt(0) {
        for (int i = 0; i < CN; ++i) {
            next[i] = NULL;
        }
    }
};

struct Trie {
    Node* root;

    Trie() {
        root = new Node();
    }
    int _get_idx(int c) {
        return c - 'a'; // *
    }

    void insert(const char* s) {
        Node* p = root;
        while (*s) {
            int idx = _get_idx(*s);
            if (p->next[idx] == NULL) {
                p->next[idx] = new Node();
            }
            ++p->next[idx]->cnt;
            p = p->next[idx];
            ++s;
        }
    }

    int search(const char* s) {
        Node* p = root;
        int ret = 0;
        while (*s) {
            int idx = _get_idx(*s);
            if (p->next[idx] == NULL) {
                return 0;
            }
            p = p->next[idx];
            ++s;
        }
        return p->cnt;
    }

    ~Trie() {
        _free(root);
    }

    void _free(Node* p) {
        for (int i = 0; i < CN; ++i) {
            if (p->next[i] != NULL) {
                free(p->next[i]);
            }
        }
        delete p;
    }
};
