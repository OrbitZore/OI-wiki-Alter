#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e6 + 10;
const int M = 20;
char s[N];
int n;
int Log[N];
int pow2[25];
struct SA
{
    int f[N][M]; // st表
    int h[N], sa[N], rk[N], x[2 * N], y[2 * N], c[N];
    int m;
    void init()
    {
        m = 30;
        for (int i = 0; i <= m; i++)c[i] = 0;
        for (int i = 1; i <= n; i++)c[x[i] = s[i] - 'a' + 1]++;
        for (int i = 1; i <= m; i++)c[i] += c[i - 1];
        for (int i = n; i >= 1; i--)sa[c[x[i]]--] = i;
        for (int k = 1; k <= n; k <<= 1)
        {
            int num = 0;
            for (int i = n; i >= n - k + 1; i--)y[++num] = i;
            for (int i = 1; i <= n; i++)
            	if (sa[i] > k)y[++num] = sa[i] - k;
            for (int i = 0; i <= m; i++)c[i] = 0;
            for (int i = 1; i <= n; i++)c[x[i]]++;
            for (int i = 1; i <= m; i++)c[i] += c[i - 1];
            for (int i = n; i >= 1; i--)
                sa[c[x[y[i]]]--] = y[i], y[i] = 0;
            for (int i = 0; i <= 2 * n; i++)swap(x[i], y[i]);
            num = 0;
            x[sa[1]] = ++num;
            for (int i = 2; i <= n; i++)
                x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? num : ++num;
            if (num == n)break;
            m = num;
        }
    }
    void getHeight()
    {
        for (int i = 1; i <= n; i++)rk[sa[i]] = i;
        for (int i = 1, k = 0; i <= n; i++)
        {
            if (rk[i] == 1)continue;
            if (k)k--;
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k])k++;
            h[rk[i]] = k;
        }
    }
    void initST()
    {
        for (int i = 1; i <= n; i++)f[i][0] = h[i];
        for (int j = 1; j <= M; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                f[i][j] = min(f[i][j - 1], f[i + pow2[j - 1]][j - 1]);
    }
    int lcp(int x, int y)
    {
        int l = rk[x];
        int r = rk[y];
        if (l > r)swap(l, r);
        l++;
        int s = Log[r - l + 1];
        return min(f[l][s], f[r - pow2[s] + 1][s]);
    }
    void main()
    {
        init();
        getHeight();
        initST();
    }
} s1, s2;
void init()
{
    for (int i = 2; i < N; i++)Log[i] = Log[i / 2] + 1;
    pow2[0] = 1;
    for (int i = 1; i < 25; i++)pow2[i] = pow2[i - 1] * 2;
}
int lcp(int x, int y)
{
    return s1.lcp(x, y);
}
int lcs(int x, int y)
{
    return s2.lcp(n - y + 1, n - x + 1);
}
LL make(int len)
{
    LL res = 0;
    for (int i = 1; i + len <= n; i += len)
    {
        if (s[i] != s[i + len])continue;
        int ll = i - lcs(i, i + len) + 1;
        int rr = i + len + lcp(i, i + len) - 1;
        if (rr - ll + 1 < 2 * len)continue;
        int num = rr - ll + 1 - (len - 1);
        int t = num / len;
        res += (num % len) * (LL)t * len;
        res += (LL)t * (t - 1) / 2 * len * len;
        i = rr - len + 1;
    }
    return res;
}
void solve()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    s1.main();
    reverse(s + 1, s + 1 + n);
    s2.main();
    reverse(s + 1, s + 1 + n);
    LL ans = 0;
    for (int i = 1; i <= n; i++)ans += (LL)i * (n - i + 1);
    for (int len = 1; len <= n / 2; len++)ans += make(len);
    printf("%lld\n", ans);
}
int main()
{
    init();
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)solve();
}