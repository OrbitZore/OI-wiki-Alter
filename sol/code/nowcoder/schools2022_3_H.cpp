#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 4e6 + 10;
int tot = 1, last = 1;
struct Node
{
    int len, fa;
    int ch[26];
} node[N];

string s;
LL f[N], ans;
int n, m, k;
LL w[N];

void extend(int c)
{
    int p = last, np = last = ++tot;
    f[tot] = 1;
    node[np].len = node[p].len + 1;
    for (; p && !node[p].ch[c]; p = node[p].fa)
        node[p].ch[c] = np;
    if (!p)
        node[np].fa = 1;
    else
    {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1)
            node[np].fa = q;
        else
        {
            int nq = ++tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa)
                node[p].ch[c] = nq;
        }
    }
}

LL tr[N], l[N], r[N], mid[N];
void create(int ll, int rr, int i)
{
    if (ll == rr)
    {
        l[i] = ll;
        r[i] = rr;
        mid[i] = ll;
        tr[i] = w[ll];
    }
    else
    {
        mid[i] = (ll + rr) >> 1;
        l[i] = ll;
        r[i] = rr;
        create(ll, mid[i], i * 2);
        create(mid[i] + 1, rr, 2 * i + 1);
        tr[i] = min(tr[2 * i], tr[2 * i + 1]);
    }
}

LL query(int L, int R, int i)
{
    if (L <= l[i] && R >= r[i])
    {
        return tr[i];
    }
    LL s = 1e18;
    if (L <= mid[i])
    {
        s = min(s, query(L, R, 2 * i));
    }
    if (mid[i] + 1 <= R)
    {
        s = min(s, query(L, R, 2 * i + 1));
    }
    return s;
}

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
}

int main()
{
    init();
    cin >> n >> m >> k;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
        extend(s[i] - 'a');

    node[1].fa = 1;
    for (int i = 1; i <= m; i++)
        cin >> w[i];
    for (int i = 1; i <= m; i++)
    {
        w[i] += w[i - 1];
    }

    create(0, m, 1);

    for (int i = 0; i < k; i++)
    {
        cin >> s;
        LL ans = 0;
        s = " " + s + " ";
        int len = 0;
        LL lasti = 0;
        for (int p = 1, i = 1; i < s.size(); i++)
        {
            if (s[i] == ' ' || node[p].ch[s[i] - 'a'] == 0)
            {
                if (len == 0)
                    continue;
                LL L = i - len;
                for (int ii = max(L, lasti); ii < i; ii++)
                {
                    ans = max(ans, w[ii] - query(L - 1, ii, 1));
                }
                i--;
                lasti = i;
                len--;
                if (node[node[p].fa].len == len)
                    p = node[p].fa;
            }
            else
            {
                p = node[p].ch[s[i] - 'a'];
                len++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}