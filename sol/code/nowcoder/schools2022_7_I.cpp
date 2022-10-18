#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using vi = vector<int>;
using vL = vector<LL>;
using pii = pair<int, int>;
using pLL = pair<LL, LL>;

#define x first
#define y second

const LL N = 4e5 + 100;
const LL mod = 1e9 + 7;

char s[N];
int a[N];
int ac[N];
int x[N], y[N], c[N];
int sa[N];
int h[N], rk[N];

vector<int> md[26];
int dp[N][26];
int pos[N];
int ct[N];
int n, m;

int am, bm;
int ca, cb;
int pa, pb;
int ll, rr, ms, rs;
void getSA()
{
    memset(x, 0x3f, sizeof x);
    for (int i = 1; i <= n; i++)
        c[x[i] = a[i]]++;
    for (int i = 1; i <= m; i++)
        c[i] += c[i - 1];
    for (int i = n; i >= 1; i--)
        sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++)
            y[++num] = i;

        for (int i = 1; i <= n; i++)
            if (sa[i] > k)
                y[++num] = sa[i] - k;

        for (int i = 0; i <= m; i++)
            c[i] = 0;
        for (int i = 1; i <= n; i++)
            c[x[i]]++;
        for (int i = 1; i <= m; i++)
            c[i] += c[i - 1];
        for (int i = n; i >= 1; i--)
            sa[c[x[y[i]]]--] = y[i], y[i] = 0;

        swap(x, y);
        num = 0;
        x[sa[1]] = ++num;
        for (int i = 2; i <= n; i++)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
        m = num;
        if (num == n)
            break;
    }

    for (int i = 1; i <= n; i++)
        rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++)
    {
        if (rk[i] == 1)
            continue;
        if (k)
            k--;
        int j = sa[rk[i] - 1];

        while (i + k <= n && j + k <= n && a[i + k] == a[j + k])
            k++;
        h[rk[i]] = k;
    }
}
const int logn = 20;
int Logn[N];
int f[N][logn];

void pre()
{ // 准备工作，初始化
    Logn[1] = 0;
    Logn[2] = 1;
    for (int i = 3; i < N; i++)
    {
        Logn[i] = Logn[i / 2] + 1;
    }
    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; i++)
        f[i][0] = h[i];

    for (int j = 1; j <= logn; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]); // ST表具体实现
}

bool cmp(int x, int y)
{
    int ps = min(n - x + 1, n - y + 1);

    for (int i = 0; i < 26; i++)
    {
        if (!dp[x][i] && !dp[y][i])
            break;
        if (dp[x][i] == 0)
        {
            ps = min(ps, dp[y][i] - y);
        }
        if (dp[y][i] == 0)
        {
            ps = min(ps, dp[x][i] - x);
        }
        if (dp[x][i] && dp[y][i])
        {
            if (dp[x][i] - x != dp[y][i] - y)
            {
                ps = min(ps, min(dp[x][i] - x, dp[y][i] - y));
            }
            else
            {
                pa = pos[dp[x][i]] + 1;
                pb = pos[dp[y][i]] + 1;
                if (a[pa] != 0 && a[pb] != 0)
                {
                    ll = min(rk[pa], rk[pb]);
                    rr = max(rk[pa], rk[pb]);
                    ll++;
                    ms = Logn[rr - ll + 1];
                    rs = min(f[ll][ms], f[rr - (1 << ms) + 1][ms]);

                    if (rs <= ct[pa])
                    {
                        ps = min(ps, ac[pa + rs] - x);
                    }
                    if (rs <= ct[pb])
                    {
                        ps = min(ps, ac[pb + rs] - y);
                    }
                }
                else if (a[pa] == 0 && a[pb] == 0)
                {
                }
                else if (a[pa] == 0)
                {
                    ps = min(ps, ac[pb] - y);
                }
                else if (a[pb] == 0)
                {
                    ps = min(ps, ac[pa] - x);
                }
            }
        }
    }

    if (x + ps > n)
        return true;
    if (y + ps > n)
        return false;
    for (int i = 0; i < 26; i++)
    {
        if (s[dp[x][i]] == s[x + ps])
            ca = i;
        if (s[dp[y][i]] == s[y + ps])
            cb = i;
    }
    if (ca == cb)
    {
        cout << x << " " << y << endl;
    }
    return ca < cb;
}

void solve()
{
    cin >> n;
    m = n + 1;
    cin >> s + 1;
    for (int i = 1; i <= n; i++)
    {
        int si = s[i] - 'a';
        md[si].push_back(i);
    }

    int cnt = 1;
    for (int i = 0; i < 26; i++)
    {
        if (md[i].size())
            a[cnt] = 0, ac[cnt] = md[i][0], pos[md[i][0]] = cnt++;
        for (int ii = 1; ii < md[i].size(); ii++)
        {
            ct[cnt - 1] = md[i].size() - ii;
            a[cnt] = md[i][ii] - md[i][ii - 1], ac[cnt] = md[i][ii], pos[md[i][ii]] = cnt++;
        }
    }

    for (int i = n; i >= 1; i--)
    {
        for (int ii = 0; ii < 26; ii++)
        {
            dp[i][ii] = dp[i + 1][ii];
        }
        int pos = 0;
        for (int ii = 0; ii < 26; ii++)
        {
            if (!dp[i][ii])
            {
                pos = ii;
                break;
            }
            else if (s[dp[i][ii]] == s[i])
            {
                pos = ii;
                break;
            }
        }
        for (int ii = pos; ii >= 1; ii--)
        {
            dp[i][ii] = dp[i][ii - 1];
        }
        dp[i][0] = i;
    }

    getSA();
    pre();
    vector<int> v(n);
    for (int i = 0; i < v.size(); i++)
        v[i] = i + 1;
    stable_sort(v.begin(), v.end(), cmp);
    for (auto x : v)
    {
        cout << x << ' ';
    }
}

int main()
{
    solve();
}