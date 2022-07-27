#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL N = 1e4 + 2;
const LL M = 2000 + 100;

int n, m, l, x, y;
int dp[2][M];

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
}

void solve()
{
    cin >> n >> m;
    int ans = N;
    
    for (int i = 1; i <= n; i++)
    {
        cin >> l;
        for (int j = 0; j <= m; j++)
            dp[i % 2][j] = dp[(i - 1) % 2][j];
        for (int j = 0; j < l; j++)
        {
            cin >> x >> y;
            if (x == 1)
            {
                dp[i % 2][y] = i;
            }
            dp[i % 2][y] = max(dp[(i - 1) % 2][x], dp[i % 2][y]);
        }
        if (dp[i % 2][m])
            ans = min(ans, i - dp[i % 2][m] + 1);
    }
    
    if (ans == N)
        ans = -1;
    cout << ans << "\n";
}

int main()
{
    init();
    solve();
}