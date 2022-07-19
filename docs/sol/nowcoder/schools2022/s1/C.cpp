#include <bits/stdc++.h>
using namespace std;
struct FAST_IO {
  FAST_IO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  }
} __fast_io;

template <class T>
using vec = vector<T>;

using ll = long long;

struct P {
  int x, y;
};
int n, m, k, q;
bool operator==(const P& a, const P& b) { return a.x == b.x && a.y == b.y; }
struct CMP0 {
  bool operator()(const P& a, const P& b) const {
    return (ll)(a.x) * (b.y - 1) - (ll)(a.y - 1) * (b.x) < 0;
  }
};
struct CMP1 {
  bool operator()(const P& a, const P& b) const {
    return (ll)(a.x) * (b.y - m) - (ll)(a.y - m) * (b.x) > 0;
  }
};
P d[200000 + 10];
int dl = 0, dr = 0;
P v[200000 + 10];
int ans[200000 + 10];
vec<P> v0, v1;
int main() {
  cin >> n >> m >> k >> q;
  for (int i = 1; i <= k; i++) {
    int x, y;
    cin >> x >> y;
    v[i] = {x, y};
    v0.push_back({x, y});
    v1.push_back({x, y});
  }
  sort(v0.begin(), v0.end(), CMP0());
  sort(v1.begin(), v1.end(), CMP1());
  for (int qi = 0; qi < q; qi++) {
    for (int i = 1; i <= m; i++) ans[i] = n;

    int pi, xi, yi;
    cin >> pi >> xi >> yi;
    v0.erase(find(v0.begin(), v0.end(), v[pi]));
    v1.erase(find(v1.begin(), v1.end(), v[pi]));
    v[pi] = {xi, yi};
    v0.insert(lower_bound(v0.begin(), v0.end(), v[pi], CMP0()), v[pi]);
    v1.insert(lower_bound(v1.begin(), v1.end(), v[pi], CMP1()), v[pi]);
    dl = dr = 0;
    for (auto p : v0) {
      if (dl == dr || d[dr - 1].y > p.y) {
        d[dr++] = p;
      }
    }
    for (int i = m; i >= 1; i--) {
      while (dl != dr && d[dl].y > i) {
        ++dl;
      }
      if (dl == dr) continue;
      auto y = d[dl].y;
      if (y == 1) {
        continue;
      }
      double x = d[dl].x;
      if (y != i) {
        x += (double)(i - y) / (y - 1) * (x);
      }
      double xx = abs(floor(x) - x) < 1e-6 ? floor(x) - 1 : floor(x);
      if (xx < ans[i]) ans[i] = xx;
    }

    dl = dr = 0;
    for (auto p : v1) {
      if (dl == dr || d[dr - 1].y < p.y) {
        d[dr++] = p;
      }
    }
    //     for (auto i:d) cerr<<i.x<<" "<<i.y<<endl;
    for (int i = 1; i <= m; i++) {
      while (dl != dr && d[dl].y < i) {
        ++dl;
      }
      if (dl == dr) continue;
      auto y = d[dl].y;
      if (y == m) {
        continue;
      }
      double x = d[dl].x;
      if (y != i) {
        x += (double)(y - i) / (m - y) * (x);
      }
      double xx = abs(floor(x) - x) < 1e-6 ? floor(x) - 1 : floor(x);
      if (xx < ans[i]) ans[i] = xx;
    }
    ll ans0 = 0;
    for (int i = 1; i <= m; i++) ans0 += ans[i];
    cout << ans0 << "\n";
  }
}