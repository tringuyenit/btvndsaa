#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 5;
const int inf = 0x3f3f3f3f;
int n, k, m;
int dp[N][2005], res = inf;
struct dat
{
    int node, val;
};
vector <dat> a[N];
void dfs(int u, int pre)
{
    dp[u][0] = 0;
    for (dat tmp : a[u])
    {
        int v = tmp.node;
        if (v == pre) continue;
        dfs(v, u);
        for (int i = 1; i <= k; ++i)
        {
            if (dp[v][i - 1] == inf) continue;
            dp[u][i] = min(dp[u][i], dp[v][i - 1] + tmp.val);
        }
    }
    res = min(res, dp[u][k]);
    if (a[u].size() > 1)
    {
        for (int i = 0; i < a[u].size(); ++i)
        {
            int v1 = a[u][i].node;
            if (v1 == pre) continue;
            for (int j = i + 1; j < a[u].size(); ++j)
            {
                int v2 = a[u][j].node;
                if (v2 == pre) continue;
                for (int t = 0; t <= k - 2; ++ t)
                {
                    res = min(res, dp[v1][t] + a[u][i].val + dp[v2][k - t - 2] + a[u][j].val);
                }
            }
        }

    }
}
void solve()
{
    cin >> n >> k >> m;
    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        a[u].push_back({v, w});
        a[v].push_back({u, w});
    }
    memset(dp, 0x3f, sizeof(dp));
    dfs(1, 0);
    cout << res;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
//    cin >> T;
    while (T--)
    {
        solve();
    }
}
