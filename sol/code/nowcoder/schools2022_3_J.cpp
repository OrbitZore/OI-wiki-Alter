#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define x first
#define y second

const int N = 5e5 + 100;

int c[N][5];
bool st[N][5];
int n, m, x, y;
int s1, s2, t1, t2;

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
}

int bfs()
{
    queue<pair<pii, int>> q;
    stack<pair<pii, int>> sc;
    q.push({{s1, s2}, 0});
    while (q.size() || sc.size())
    {
        if (q.size() == 0)
        {
            while (sc.size())
            {
                q.push(sc.top());
                sc.pop();
            }
        }
        if (!q.size())
            break;
        auto s = q.front();
        q.pop();
        if (s.x.x == t1 && s.x.y == t2)
        {
            return s.y;
        }
        int x = s.x.x;
        int y = s.x.y;
        int pos = 1;
        for (int i = 1; i <= 4; i++)
        {
            if (c[y][i] == x)
            {
                pos = i;
                break;
            }
        }
        if (st[y][pos])
            continue;
        st[y][pos] = 1;
        q.push({{y, c[y][pos % 4 + 1]}, s.y});
        for (int i = 2; i <= 4; i++)
        {
            int yy = (pos + i - 1) % 4 + 1;
            sc.push({{y, c[y][yy]}, s.y + 1});
        }
    }
    return -1;
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            cin >> c[i][j];
        }
    }
    cin >> s1 >> s2 >> t1 >> t2;
    cout << bfs() << "\n";
}

int main()
{
    init();
    solve();
}