#include <bits/stdc++.h>

using namespace std;

struct FAST_IO {
  FAST_IO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  }
};

template <class T>
using vec = vector<T>;

int main() {
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++)
    cout << "Case #" << Ti << ": " << []() -> int {
      int n;
      cin >> n;
      vec<set<int>> G(n);

      vec<int> ins(n, 0);
      queue<pair<int, int>> tomerge;

      vec<int> mfset(n);
      vec<int> sz(n, 1);

      iota(mfset.begin(), mfset.end(), 0);

      function<int(int)> fa = [&](int i) {
        return mfset[i] == i ? i : (mfset[i] = fa(mfset[i]));
      };

      auto merge = [&](int i, int j) {  // i->j
        if (i == j)
          return;
        mfset[i] = j;
        sz[j] += sz[i];
        auto &Gii = G[i], &Gjj = G[j];
        if (Gii.size() > Gjj.size())
          swap(Gii, Gjj);
        for (auto Gi : Gii) {
          auto Gji = Gjj.find(Gi);
          if (Gji == Gjj.end()) {
            Gjj.insert(Gi);
          } else {
            if (--ins[Gi] == 1)
              tomerge.push({Gi, j});
          }
        }
      };
      for (int i = 0; i < n; i++) {
        int k;
        cin >> ins[i];
        for (int j = 0; j < ins[i]; j++) {
          cin >> k;
          k--;
          G[k].insert(i);
        }
        if (ins[i] == 1)
          tomerge.push({i, k});
      }
      while (tomerge.size()) {
        int u = fa(tomerge.front().first), v = fa(tomerge.front().second);
        tomerge.pop();
        merge(u, v);
      }
      int ans = 0;
      for (int i = 0; i < n; i++) {
        ans = max(ans, sz[i]);
      }
      return ans;
    }() << endl;
}