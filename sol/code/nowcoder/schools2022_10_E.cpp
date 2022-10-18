#include <bits/stdc++.h>
#define N 1005
#define M 1005
using namespace std;
template <class T>
using vec = vector<T>;
bool FG[N][N];
multiset<int> ma[N];
int book[N], maxn = 0;
int n, m, e;
vec<int> v;
int dfs(int l, int p = 1000000) {
  book[l] = 1;
  int i = 0;
  bool f = true;
  int vs = 1000000, vvi;
  for (; i < v.size(); i++)
    if (FG[l][v[i]]) {
      int vi = v[i];
      if (exchange(f, false))
        vs = ma[vvi = vi].size();
      if (ma[vi].size() == 0) {
        ma[vi].insert(l);
        return vi;
      }
      for (auto j = ma[vi].begin(); j != ma[vi].end(); j++) {
        if ((!book[*j]) && dfs(*j, min(p, vs))) {
          ma[vi].erase(j);
          ma[vi].insert(l);
          return vi;
        }
      }
    }
  if ((!f) && vs < p) {
    ma[vvi].insert(l);
    return i;
  }
  return 0;
}
char gc() {
  char c;
  while ((c = cin.get()) && c != '0' && c != '1')
    ;
  return c;
}
int to[N];
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++)
      if (gc() == '1') {
        FG[i][j] = 1;
      }
  }
  v.resize(m);
  iota(v.begin(), v.end(), 1);
  for (int i = 1; i <= n; i++) {
    sort(v.begin(), v.end(),
         [](auto&& a, auto&& b) { return ma[a].size() < ma[b].size(); });
    dfs(i);
    memset(book, 0, sizeof(book));
  }
  for (int i = 1; i <= m; i++) {
    for (auto j : ma[i]) {
      to[j] = i;
    }
  }
  for (int i = 1; i <= n; i++)
    if (to[i] == 0) {
      cout << -1 << endl;
      return 0;
    }
  for (int i = 1; i <= n; i++)
    cout << to[i] << " ";
  cout << endl;
}