#include <bits/stdc++.h>
using namespace std;

const LL N = 110;

int a[N];
int n, m, x, y, k, t, q, c;

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
}

void insert(int p, int num)
{
    for (int i = c; i >= p; i--)
    {
        a[i] = a[i - 1];
    }
    a[p] = num;
    y++, c++;
}
void solve()
{
    cin >> m;
    if (m == 1)
    {
        cout << 1 << "\n" << 1 << "\n";
        return;
    }
    x = m;
    k = -1;
    while (x)
    {
        x /= 2;
        k++;
    }
    for (int i = 0; i < 2 * k; i += 2)
    {
        a[i] = i + 2;
        a[i + 1] = i + 1;
    }
    c = 2 * k;
    x = m;
    y = 2 * k + 1;
    t = 0;
    int pos = 0, f = 0;
    for (int i = 0; i < k; i++)
    {
        t++;
        if (x % 2)
        {
            while (a[pos] != 2 * t)
                pos++;
            insert(pos, y);
            f = 1;
        }
        else if (f)
        {
            pos++;
            insert(pos, y);
        }
        x /= 2;
    }
    cout << c << "\n";
    for (int i = 0; i < c; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main()
{
    init();
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }
}