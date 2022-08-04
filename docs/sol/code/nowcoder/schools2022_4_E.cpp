#include <bits/stdc++.h>
using namespace std;
struct FAST_IO {
  FAST_IO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  }
} __fast_io;
#define x first
#define y second
#define all(a) (a).begin(), (a).end()
using ll = long long;
template <class T>
using vec = vector<T>;

bool MULTIDATA = true;

#define mod (998244353)
int seed, n, q, m;
int D[405][405][405], A[405][405][405];

void insert(map<int, int>& m, const int x, const int y, const int z) {
  auto maintain = [&](map<int, int>::iterator i, const int a) {  // insert=1
    auto ri = reverse_iterator<map<int, int>::iterator>(i);
    auto ii = next(i);
    D[i->x][i->y][z] += a;
    if (ii != m.end())
      D[ii->x][i->y][z] -= a;
    if (ri != m.rend())
      D[i->x][ri->y][z] -= a;
    if (ii != m.end() && ri != m.rend())
      D[ii->x][ri->y][z] += a;
  };
  auto w = m.upper_bound(x);
  if (w != m.begin()) {
    auto pw = prev(w);
    if (pw->y <= y)
      return;
    if (pw->x == x) {
      maintain(pw, -1);
      m.erase(pw);
    }
  }
  for (auto wn = m.upper_bound(x); wn != m.end() && wn->y >= y;) {
    maintain(wn, -1);
    wn = m.erase(wn);
  }
  auto mi = m.insert({x, y});
  w = mi.x;
  maintain(w, 1);
}
int solve(int a, int b, int c) {
  return D[a][b][c];
}
int main() {
  cin >> n >> q;
  for (int t = 0; t < n; t++) {
    int m;
    cin >> m;
    vec<array<int, 3>> mv;
    for (int j = 1; j <= m; j++) {
      int a, b, c;
      cin >> a >> b >> c;
      mv.push_back({c, a, b});
    }
    sort(all(mv));
    map<int, int> F;
    for (const auto& [z, x, y] : mv) {
      insert(F, x, y, z);
    }
  }

  for (int i = 1; i <= 400; i++)
    for (int j = 1; j <= 400; j++)
      for (int k = 1; k <= 400; k++)
        D[i][j][k] += D[i - 1][j][k] + D[i][j - 1][k] + D[i][j][k - 1] -
                      D[i - 1][j - 1][k] - D[i - 1][j][k - 1] -
                      D[i][j - 1][k - 1] + D[i - 1][j - 1][k - 1];
  cin >> seed;
  mt19937 rng(seed);
  uniform_int_distribution<> u(1, 400);
  int lastans = 0;
  ll ans = 0;
  for (int i = 1; i <= q; i++) {
    int IQ = (u(rng) ^ lastans) % 400 + 1;  // The IQ of the i-th friend
    int EQ = (u(rng) ^ lastans) % 400 + 1;  // The EQ of the i-th friend
    int AQ = (u(rng) ^ lastans) % 400 + 1;  // The AQ of the i-th friend
    lastans = solve(IQ, EQ, AQ);            // The answer to the i-th friend
    ans = (ans * seed + lastans) % mod;
  }
  cout << ans << endl;
}

