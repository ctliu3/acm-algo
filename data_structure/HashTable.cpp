// Implementation of Hash Table. Use separate chaining to solve the collision (
// as STL do).

const int TABLE_SIZE = 1000 + 5;

template <typename T>
class Key {
  T m_data;
  size_t m_code;

public:
  explicit Key(const T& key) {
    this->m_data = key;

    string data = get_data();
    this->m_code = 0;
    for (auto c : data) {
      this->m_code += c;
      this->m_code %= TABLE_SIZE;
    }
  }

  string get_data() const {
    ostringstream os;
    os << m_data;
    return os.str();
  }

  size_t hashcode() const {
    return m_code;
  }

  bool operator==(const Key<T>& o) const {
    return m_data == o.m_data;
  }
};

template <typename K_, typename V_>
class HashTable {
  size_t m_size;
  vector<list<pair<K_, V_>>> m_table;

public:
  explicit HashTable() {
    this->m_size = TABLE_SIZE;
    this->m_table.resize(m_size, list<pair<K_, V_>>());
  }

  explicit HashTable(int size) {
    this->m_size = size;
    this->m_table.resize(m_size, list<pair<K_, V_>>());
  }

  void insert(const K_& key, const V_ value) {
    size_t hashcode = key.hashcode();
    list<pair<K_, V_>>& lst = this->m_table[hashcode];

    // Collision resolution by chaining
    if (lst.size()) {
      for (auto& item : lst) {
        if (item.first == key) {
          item.second = value;
          return ;
        }
      }
    }

    lst.push_back({key, value});
  }

  void erase(const K_& key) {
    size_t hashcode = key.hashcode();
    list<pair<K_, V_>>& lst = m_table[hashcode];
    typedef typename list<pair<K_, V_>>::iterator LIST_ITERATOR;

    for (LIST_ITERATOR itr = lst.begin(); itr != lst.end(); ++itr) {
      if (itr->first == key) {
        lst.erase(itr);
        break;
      }
    }
  }

  V_& operator[](K_ key) {
    size_t hashcode = key.hashcode();
    list<pair<K_, V_>>& lst = m_table[hashcode];
    assert(lst.size() != 0);

    for (auto& item : lst) {
      if (item.first == key) {
        return item.second;
      }
    }
    assert(true);
  }
};

int main() {
  HashTable<Key<int>, string> ht;
  Key<int> key1 = Key<int>(10);
  Key<int> key2 = Key<int>(20);
  ht.insert(key1, "hello");
  ht.insert(key2, "world");
  ht.insert(key1, "goodbye");

  cout << ht[key1] << endl;
  cout << ht[key2] << endl;
  return 0;
}
