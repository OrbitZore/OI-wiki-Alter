#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

#define pb push_back
#define x first
#define y second

const LL S = 2e7 + 100;
const LL N = 2e6 + 100;

char str[S];
string s;
vector<string> v;

int cnt = 0;
int n;
int tr[S][6], idx;
int st[S];
int num[S];
int z[S];
pair<int, int> out[N];
int res;
bool yes[N];

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
}

void insert()
{
    static int cnt = 0;
    int p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int c = s[i] - '0';
        if (!tr[p][c])
        {
            tr[p][c] = ++idx;
        }
        p = tr[p][c];
    }
    st[p]++;
    if (num[p] == -1)
    {
        v[cnt] = s;
        num[p] = cnt++;
    }
}

void updateZ()
{
    memset(z, 0, sizeof(int) * (cnt + 1));
    for (int i = 1, l = 0, r = 0; i < cnt; i++)
    {
        if (i <= r && z[i - l] < r - i + 1)
            z[i] = z[i - l];
        else
        {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < cnt && str[z[i]] == str[i + z[i]])
                z[i]++;
        }
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}

void output(int up, int stu)
{
    out[res++] = {num[up], stu};
    vector<int> vv;
    for (int i = 0, p = 0; i < cnt - 1; i++)
    {
        p = tr[p][str[i] - '0'];
        if (st[p])
        {
            int len = v[num[p]].size();
            if (z[len] == cnt - len)
            {
                len = z[len];
                if (str[(len + z[len]) % cnt] > str[z[len] % cnt])
                {
                    yes[num[p]] = 1;
                    vv.push_back(num[p]);
                }
            }
            else if (str[(len + z[len]) % cnt] < str[z[len] % cnt])
            {
                yes[num[p]] = 1;
                vv.push_back(num[p]);
            }
        }
    }
    for (int k = res - 2; k >= 0; k--)
    {
        if (yes[out[k].x])
            swap(out[k + 1], out[k]);
        else
            break;
    }
    for (auto x : vv)
        yes[x] = 0;
}

int stack_p[S], stack_cnt[S], sid;
char stack_s[S];

void dfs(int u)
{
    stack_p[sid] = u;
    stack_cnt[sid] = 0;
    sid++;
    while (sid != 0)
    {
        int u = stack_p[sid - 1];
        cnt = stack_cnt[sid - 1];
        if (cnt)
        {
            str[cnt - 1] = stack_s[sid - 1];
        }
        sid--;
        if (st[u])
        {
            updateZ();
            output(u, st[u]);
        }
        for (int i = 4; i >= 0; i--)
        {
            if (tr[u][i])
            {
                stack_p[sid] = tr[u][i];
                stack_cnt[sid] = cnt + 1;
                stack_s[sid] = '0' + i;
                sid++;
            }
        }
    }
}

void solve()
{
    cin >> n;
    v.resize(n);
    memset(num, -1, sizeof num);
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        insert();
    }
    dfs(0);
    for (int i = 0; i < res; i++)
    {
        for (int j = 0; j < out[i].y; j++)
            cout << v[out[i].x];
    }
}

int main()
{
    init();
    solve();
}