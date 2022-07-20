#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL mod = 1e9 + 7;
const LL N = 2e5 + 100;

LL t, n, m, x, y, k;
LL dp[8][136]; // 还缺i个对子，牌堆还有j张牌获胜的期望
LL inv[136];
LL ksm(LL x, LL y)
{
    if (y == 0)
        return 1;
    if (y == 1)
        return x % mod;
    LL as = ksm(x, y / 2);
    if (y % 2)
        return as * as % mod * x % mod;
    return as * as % mod;
}

LL mint(LL x)
{
    return x % mod;
}
void init()
{
    for (int i = 1; i < 136; i++)
    {
        inv[i] = ksm(i, mod - 2);
    }
    for (int i = 1; i <= 7; i++)
    {
        for (int j = i; j <= 123; j++)
        {
            dp[i][j] = mint(dp[i - 1][j - 1] + 1) * mint((6 * i - 3) * inv[j]) % mod +
                       mint(dp[i][j - 1] + 1) * mint((j - 6 * i + 3) * inv[j]) % mod;
            dp[i][j] %= mod;
        }
        // cout << dp[i][123] << endl;
    }
}

string s[13];
void solve()
{
    char x[3];

    for (int i = 0; i < 13; i++)
    {
        scanf("%2s", x);
        swap(x[0], x[1]);
        s[i] = x;
    }
    sort(s, s + 13);
    int cnt = 0;
    for (int i = 1; i < 13; i++)
        if (s[i] == s[i - 1])
            cnt++;

    cout << dp[7 - cnt][123] << "\n";
}

int main()
{
    init();
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cout << "Case #" << i << ": ";
        solve();
    }
}