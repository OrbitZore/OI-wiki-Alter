#include <bits/stdc++.h>
using namespace std;
struct FAST_IO {
  FAST_IO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  }
} __fast_io;
template <class T1, class T2>
bool cmin(T1& a, const T2 b) {
  return a > b ? a = b, 1 : 0;
}

bool MULTIDATA = true;

int n, ci;
array<int, 3> c[8011];
int a[8011], b[8011], DP[8011][8011];
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  a[0] = 0x3f3f3f3f;
  memset(DP, 0x3f, sizeof(DP));
  DP[0][0] = 0;
  for (int k = 1; k <= n; k++) {
    ci = 0;
    if (k == 1)
      c[ci++] = {a[1], DP[k - 1][0],DP[k - 1][0]+a[1]};
    for (int i = 1; i <= n; i++) {
      if (ci){
        DP[k][i] = c[ci-1][2];
      }
      if (i != n) {
        if (ci && c[ci - 1][0] <= a[i + 1]) {
          int f = ci - 1;
          while (f != 0 && c[f - 1][0] <= a[i + 1])
            f--;
          c[f] = *min_element(&c[f], &c[ci],
                              [](auto&& a, auto&& b) { return a[1] < b[1]; });
          c[f][0] = a[i + 1];
          c[f][2] = c[f][0]+c[f][1];
          if (f!=0)
            cmin(c[f][2],c[f-1][2]);
          ci = f + 1;
        }
        if (DP[k - 1][i] != 0x3f3f3f3f){
          c[ci] = {a[i + 1], DP[k - 1][i],a[i + 1]+DP[k - 1][i]};
          if (ci!=0){
            cmin(c[ci][2],c[ci-1][2]);
          }
          ci++;
        }
      }
    }
    cout << DP[k][n] << endl;
  }
}