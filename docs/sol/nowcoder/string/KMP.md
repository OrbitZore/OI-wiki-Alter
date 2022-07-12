### C:[栗酱的数列](https://ac.nowcoder.com/acm/contest/27589/C)
栗酱有一个长度为n的数列A，一个长度为m的数列B，现在询问A中有多少个长度为m的连续子序列A'，满足$(a^{'}_{1}+b_1)\%k=(a^{'}_{2}+b_2)\%k=...=(a^{'}_{m}+b_m)\%k$
#### 思路
将上述式子变形得到$(a^{'}_{1}+b_1)\%k-(a^{'}_{2}+b_2)\%k=0$进而化简成
$(a^{'}_{2}-a^{'}_{1} +b_{2} - b_{1})\%k=0$，因此我们可以构造新的数组，使得$A_{i+1}=a_{i+1}-a_i$,$B_{i+1}=b_{i+1}-b_i$，用新的A数组匹配B数组。
此时，只需要对B数组跑一个next数组，利用KMP对A数组进行匹配即可。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

#define pb push_back
#define endl "\n"

const LL mod = 1e9 + 7;
const LL N = 2e5 + 100;

LL a[N];
LL aa[N];
LL b[N];
LL bb[N];
int nxt[N];
LL t, n, m, x, y, k;

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
}

void getNext()
{
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j && bb[i] != bb[j + 1])
            j = nxt[j];
        if (bb[i] == bb[j + 1])
            j++;
        nxt[i] = j;
    }
}
void solve()
{
    cin >> n >> m >> k;
    memset(nxt, 0, sizeof nxt);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] %= k;
    }
    for (int i = 1; i < n; i++)
    {
        aa[i] = (a[i + 1] - a[i] + k) % k;
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> b[i];
        b[i] %= k;
    }
    for (int i = 1; i < m; i++)
    {
        bb[i] = (b[i + 1] - b[i] + k) % k;
    }
    getNext();
    int ans = 0;
    if (m == 1)
        ans = n;
    for (int i = 1, j = 0; i < n; i++)
    {
        while (j && (aa[i] + bb[j + 1]) % k != 0)
            j = nxt[j];
        if ((aa[i] + bb[j + 1]) % k == 0)
        {
            j++;
        }
        if (j == m - 1)
        {
            j = nxt[j];
            ans++;
        }
    }
    cout << ans << endl;
}

int main()
{
    init();
    cin >> t;
    while (t--)
    {
        solve();
    }
}
```