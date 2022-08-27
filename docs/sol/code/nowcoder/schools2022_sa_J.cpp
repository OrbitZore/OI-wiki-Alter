#include <bits/stdc++.h>
using namespace std;
struct FAST_IO {
  FAST_IO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  }
} __fast_io;

constexpr int nxt[3] = {1, 2, 0};

int a[1000000 + 1], b[2000000 + 1];
int s[2000000 + 1];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    cout << ([&]() {
      for (int i = 0; i < n; i++) {
        b[i] = a[i];
        int j = i;
        while (j > 0 && nxt[b[i]] != b[j - 1])
          j = s[j - 1];
        s[i] = j;
        if (i - s[i] + 1 >= n)
          return true;
      }
      for (int i = n; i < n * 2; i++) {
        b[i] = a[i - n];
        int j = i;
        while (j > 0 && nxt[b[i]] != b[j - 1])
          j = s[j - 1];
        s[i] = j;
        if (i - s[i] + 1 >= n)
          return true;
      }
      return false;
    }()
                 ? "Yes"
                 : "No")
         << endl;
  }
}