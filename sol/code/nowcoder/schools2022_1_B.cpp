#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 8e5 + 10;
int tot = 1, last = 1;
struct Node
{
    int len, fa;
    int ch[10];
} node[N];
char str[N];
LL f[N], ans;
int h[N], e[N], ne[N], idx;

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

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u)
{
    for (int i = h[u]; ~i; i = ne[i])
    {
        dfs(e[i]);
        f[u] += f[e[i]];
    }
}

void getAns()
{
    for (int x = 1; x <= tot; x++)
    {
        for (int i = 0; i < 9; i++)
        {
            int q = node[x].ch[i];
            int p = node[x].ch[i + 1];
            while (q && p)
            {
                ans += (node[x].len - node[node[x].fa].len) * f[q] * f[p];
                q = node[q].ch[9];
                p = node[p].ch[0];
            }
        }
    }
}
int main()
{
    int n;
    cin >> n;
    node[0].len = -1;
    scanf("%s", str);
    for (int i = 0; str[i]; i++)
        extend(str[i] - '0');
    memset(h, -1, sizeof h);
    for (int i = 2; i <= tot; i++)
        add(node[i].fa, i);
    dfs(1);
    getAns();
    cout << ans << endl;
    return 0;
}