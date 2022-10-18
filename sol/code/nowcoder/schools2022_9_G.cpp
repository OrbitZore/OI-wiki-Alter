#include <bits/stdc++.h>
using namespace std;
const int maxn = 300000 + 5;
int k;
struct PAM
{
    int sz, tot, last;
    int cnt[maxn], ch[maxn][26], len[maxn], fail[maxn];
    char s[maxn];

    int node(int l)
    { // 建立一个新节点，长度为 l
        sz++;
        memset(ch[sz], 0, sizeof(ch[sz]));
        len[sz] = l;
        fail[sz] = cnt[sz] = 0;
        return sz;
    }

    void clear()
    { // 初始化
        sz = -1;
        last = 0;
        s[tot = 0] = '$';
        node(0);
        node(-1);
        fail[0] = 1;
    }

    int getfail(int x)
    { // 找后缀回文
        while (s[tot - len[x] - 1] != s[tot])
            x = fail[x];
        return x;
    }

    void insert(char c)
    { // 建树
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a'])
        {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            ch[now][c - 'a'] = x;
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
    }
} pam[5];
char s[maxn];

int p[5] = {0, 0, 0, 0, 0};
int ans;

bool st[maxn];

void dfs()
{
    for (char a = 0; a < 26; a++)
    {
        int mp[5] = {1, 1, 1, 1, 1};
        memcpy(mp, p, sizeof p);
        bool f = false;
        for (int i = 0; i < k; i++)
        {
            if (pam[i].ch[p[i]][a])
            {
                p[i] = pam[i].ch[p[i]][a];
            }
            else
            {
                f = true;
                break;
            }
        }
        if (!f && !st[p[0]])
        {
            ans++;
            st[p[0]] = 1;
            dfs();
        }
        memcpy(p, mp, sizeof p);
    }
    if (p[0] != 1)
    {
        for (int i = 0; i < k; i++)
        {
            p[i] = pam[i].fail[p[i]];
        }
        if(!st[p[0]])
            dfs();
    }
}
int main()
{
    cin >> k;
    for (int x = 0; x < k; x++)
    {
        scanf("%s", s + 1);
        pam[x].clear();
        for (int i = 1; s[i]; i++)
        {
            pam[x].insert(s[i]);
        }
    }
    dfs();
    cout << ans << endl;
    return 0;
}