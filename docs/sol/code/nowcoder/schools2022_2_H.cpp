#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

#define x first
#define y second

int t, n, m, x, y, k;

multiset<pair<int, int>> up;
multiset<pair<int, int>> dn;

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
}

void f(multiset<pair<int, int>> &dn)
{
    if (dn.empty())
        return;
    vector<pair<int, int>> v;
    multiset<int> vi;
    for (auto x = dn.rbegin(); x != dn.rend(); x++)
    {
        if (vi.size() < m)
        {
            v.push_back(*x);
            vi.insert(x->y);
        }
        else if (x->x <= *vi.rbegin())
        {
            auto it = vi.end();
            it--;
            vi.erase(it);
            vi.insert(x->y);
            v.push_back(*x);
        }
    }
    for (auto x : v)
    {
        dn.erase(dn.lower_bound(x));
    }
}
void solve()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> x >> y;
        if (x < y)
            up.insert({y, x});
        else
            dn.insert({x, y});
    }
    LL ans = 0;
    while (up.size() || dn.size())
    {
        LL ux = 0;
        LL dx = 0;
        if (up.size())
            ux = up.rbegin()->x;
        if (dn.size())
            dx = dn.rbegin()->x;
        LL mx = max(ux, dx);
        f(dn);
        f(up);
        ans += 2 * mx - 2;
    }
    cout << ans << "\n";
}

int main()
{
    init();
    solve();
}