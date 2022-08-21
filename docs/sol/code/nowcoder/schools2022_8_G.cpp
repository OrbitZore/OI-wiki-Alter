#include <bits/stdc++.h>
using namespace std;
struct FAST_IO {
  FAST_IO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  }
} __fast_io;
#define DEF_NUM(num)           \
  using i##num = int##num##_t; \
  using u##num = uint##num##_t;
DEF_NUM(8) DEF_NUM(16) DEF_NUM(32) DEF_NUM(64) using i128 = __int128;
using u128 = unsigned __int128;

bool MULTIDATA = true;

int T;
#define N (1000000 + 10)
namespace splay {
struct node {
  node *ch[2], *fa;
  int val, minn, size;
  bool chi() { return fa->ch[1] == this; }
  node*& chf() { return fa->ch[chi()]; }
  void maintain() {
    minn = min({val, ch[0]->minn, ch[1]->minn});
    size = 1 + ch[0]->size + ch[1]->size;
  }
};
node nilnode{{&nilnode, &nilnode}, &nilnode, -1, 100000000, 0};
node* nil = &nilnode;
node d[N];
void rotate(node* a, bool d, node* b) {
  node* c = b->ch[!d];
  if (a->fa) {
    a->chf() = b;
  }
  tie(a->ch[d], b->ch[!d]) = make_tuple(c, a);
  tie(a->fa, b->fa, c->fa) = make_tuple(b, a->fa, a);
  a->maintain();
  b->maintain();
}
bool uprotate(node* b) {
  if (!b->fa)
    return false;
  rotate(b->fa, b->chi(), b);
  return true;
}
bool downrotate(node* a, bool d) {
  if (a->ch[!d] == nil)
    return false;
  rotate(a, !d, a->ch[!d]);
  return true;
}
void init(int n) {
  for (int i = 1; i <= n; i++) {
    d[i] = {{nil, nil}, NULL, i, i, 1};
  }
}

void splay(node* e) {
  while (e->fa) {
    uprotate(e);
  }
}

node* _kth(node* a, int i) {  // 1-indexed
  assert(a != nil);
  if (i <= a->ch[0]->size)
    return _kth(a->ch[0], i);
  if (i == a->ch[0]->size + 1)
    return a;
  return _kth(a->ch[1], i - a->ch[0]->size - 1);
}
node* kth(node* a, i64 i) {  // loop handler
                             //  dprint(a);
  return _kth(a, (i - 1) % a->size + 1);
}
node* spin(node* a, bool d) {
  node* b;
  while (true) {
    b = a->ch[!d];
    if (b == nil)
      break;
    rotate(a, !d, b);
    a = b;
  }
  return a;
}
pair<node*, bool> sspin(node* a, bool d1, bool d2) {
  // d1==d2 d1==0 insert_front 1 insert_back
  // d1!=d2 d1==0
  node* as = a->ch[d1];
  if (as == nil)
    return {a, d1};
  as = spin(as, d2);
  return {as, !d2};
}

void split(node* a, node* b) {
  // if (a == b) return;
  // splay(b);
  // splay(a);
  bool f = b->chi();
  if (f) {
    tie(a->ch[f], b->ch[f], b->ch[!f]) = make_tuple(b->ch[f], b->ch[!f], nil);
    a->ch[f]->fa = a;
    b->fa = NULL;
    b->ch[f]->fa = b;
  } else {
    std::swap(a->ch[1], b->ch[1]);
    a->ch[1]->fa = a;
    b->ch[1]->fa = b;
    a->ch[0] = nil;
    b->fa = NULL;
  }
  a->maintain();
  b->maintain();
}

void merge(node* a, node* b) {
  // if (a==b) return ;
  // splay(b);
  // splay(a);
  auto ass = sspin(a, 1, 1);
  node* bs = sspin(b, 1, 0).first;
  if (bs != b) {
    tie(bs->ch[1], b->ch[1]) = make_tuple(b, nil);
    tie(bs->fa, b->fa) = make_tuple((node*)NULL, bs);
    b->maintain();
    bs->maintain();
  }
  ass.first->ch[ass.second] = bs;
  bs->fa = ass.first;
  ass.first->maintain();
  if (ass.first != a)
    a->maintain();
}

bool swap(node* a, node* b) {
  // splay(b);
  // splay(a);
  if (b->fa == a) {
    split(a, b);
    return true;
  } else {
    merge(a, b);
    return false;
  }
}
}  // namespace splay

namespace sgtree {
template <class T>
T gcd(T a, T b) {
  return b == 0 ? a : gcd(b, a % b);
}
i64 lcm(i64 a, i64 b) {
  i128 ans = (i128)a * b / gcd(a, b);
  if (ans >= numeric_limits<i64>::max())
    return numeric_limits<i64>::max();
  return ans;
}
i64 nodes[8 * N];
void maintain(int i) {
  nodes[i] = lcm(nodes[i << 1], nodes[i << 1 | 1]);
}
int base;
void init(int n) {
  base = 1;
  while (base < n + 1)
    base <<= 1;
  for (int i = 1; i < base * 2; i++)
    nodes[i] = 1;
}
void set(int i, int a) {
  i += base;
  nodes[i] = a;
  while (i >>= 1) {
    maintain(i);
  }
}
int next(int i) {
  if (i == 1)
    return 4 * N;
  while (i & 1)
    i >>= 1;
  return i ^ 1;
}
int search(i64 a, i64 b) {
  int i = 1;
  while (1) {
    if (i >= base * 2)
      break;
    if (a % nodes[i] == b % nodes[i])
      i = next(i);
    else if (i >= base)
      break;
    else
      i <<= 1;
  }
  return i - base;
}
};  // namespace sgtree

namespace a {
int arr[N];
void init(int n) {
  for (int i = 1; i <= n; i++)
    arr[i] = i;
}
void swap(int i, int j) {
  std::swap(arr[i], arr[j]);
}
int get(int i) {
  return arr[i];
}
};  // namespace a
int main() {
  cin >> T;
  while (T--) {
    int n, q;
    cin >> n >> q;
    splay::init(n);
    sgtree::init(n);
    a::init(n);
    string str;
    i64 x, y;
    while (q--) {
      cin >> str >> x >> y;
      if (str == "cmp") {
        int lst = sgtree::search(x, y);
        if (lst > n) {
          cout << "=\n";
          continue;
        }
        splay::node* a = &splay::d[lst];
        splay::splay(a);
        auto f = [&](i64 i, int j) {
          if (i == 0)
            return j;
          return splay::kth(a, a->ch[0]->size + 1 + i)->val;
        };
        int ai = f(x - 1, lst), bi = f(y - 1, lst);
        int aa = a::get(ai), ba = a::get(bi);
        if (aa < ba)
          cout << "<\n";
        else
          cout << ">\n";
      } else if (str == "swap_a") {
        a::swap(x, y);
      } else if (str == "swap_p") {
        if (x == y)
          continue;
        splay::node *a = &splay::d[x], *b = &splay::d[y];
        splay::splay(b);
        splay::splay(a);
        sgtree::set(a->minn, 1);
        sgtree::set(b->minn, 1);
        if (splay::swap(a, b)) {
          sgtree::set(b->minn, b->size);
          sgtree::set(a->minn, a->size);
        } else {
          sgtree::set(a->minn, a->size);
        }
      }
    }
  }
}