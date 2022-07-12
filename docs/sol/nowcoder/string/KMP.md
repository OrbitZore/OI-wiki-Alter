### C:[栗酱的数列](https://ac.nowcoder.com/acm/contest/27589/C)
栗酱有一个长度为n的数列A，一个长度为m的数列B，现在询问A中有多少个长度为m的连续子序列A'，满足$(a^{'}_{1}+b_1)\%k=(a^{'}_{2}+b_2)\%k=...=(a^{'}_{m}+b_m)\%k$
#### 思路
将上述式子变形得到$(a^{'}_{1}+b_1)\%k-(a^{'}_{2}+b_2)\%k=0$进而化简成
$(a^{'}_{2}-a^{'}_{1} +b_{2} - b_{1})\%k=0$，因此我们可以构造新的数组，使得$A_{i+1}=a_{i+1}-a_i$,$B_{i+1}=b_{i+1}-b_i$，用新的A数组匹配B数组。
此时，只需要对B数组跑一个next数组，利用KMP对A数组进行匹配即可。

#### 样例
**输入**
```
2
3 2 5
7 8 7
8 7
3 2 5
7 8 9
8 7
```
**输出**
```
1
2
```
**数据范围**
```
T≤15,
2≤m≤n≤2×105,
1≤ai,bi,k≤109
```
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

### D:[K匹配](https://ac.nowcoder.com/acm/contest/27589/D)
给定一个长度为n的字符串S和一个长度为k的字符串T，现在牛牛想知道S有多少个子串和T是满足k匹配的。(T能够在该子串至少匹配出一个)

#### 思路
不难想到，可以用KMP在S里找到所有的T的位置。此时问题转化为，选择一个区间至少包含1一个目标区间的选择个数。对于区间选择，选择一个左边界和一个右边界。记录T在S的起始位置为$s_i$，则T串所在区间为$[s_i,s_i+k-1]$。不难发现，包含该区间的区间数为$s_i\times (n - s_i - k + 2)$，当有另外一个区间$[s_j,s_j+k-1](s_j > s_i)$时，它的选择会产生重复，根据容斥原理可知重复的部分为$左边界[1,s_i-1]$的部分。为此，根据容斥原理最终计数应为$\sum_{i=1}^{m}(s_i-s_{i-1})\times (n - s_i - k + 2)$

#### 样例
**输入**
```
10 2
abaaaababa
ab
```
**输出**
```
33
```

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

const int MAX = 1e7 + 10;
long long n, k;
char s[MAX];
char t[MAX];
int nxt[MAX];

void getNext(char *str)
{
    for (int i = 2, j = 0; str[i]; i++)
    {
        while (j && str[i] != str[j + 1])
            j = nxt[j];
        if (str[i] == str[j + 1])
            j++;
        nxt[i] = j;
    }
}

long long get(long long len)
{
    return len * (len + 1) / 2;
}
int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> k;
    cin >> s + 1;
    cin >> t + 1;
    getNext(t);

    vector<long long> v;
    v.push_back(0);
    for (int i = 1, j = 0; s[i]; i++)
    {
        while (j && s[i] != t[j + 1])
            j = nxt[j];
        if (s[i] == t[j + 1])
            j++;
        if (j == k)
        {
            v.push_back(i - k + 1);
            j = nxt[j];
        }
    }

    long long ans = 0;
    for (int i = 1; i < v.size(); i++)
    {
        ans += (v[i] - v[i - 1]) * (n - v[i] - k + 2);
    }
    cout << ans << endl;
}
```