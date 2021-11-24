#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 2;
struct edge
{
    int node;
    long long weight;
    bool operator > (const edge &a) const
    {
        return weight > a.weight;
    }
};
vector <edge> a[N];
long long d[N];
int n, m, st, fin;
priority_queue <edge, vector <edge>, greater <edge> > pq;
void dijk()
{
    for (int i = 1; i <= n; ++i)
    {
        d[i] = 1e18;
    }
    d[st] = 0;
    pq.push({st, 0});
    while (!pq.empty())
    {
        edge p = pq.top(); pq.pop();
        int u = p.node;
        long long cur = p.weight;
        if (d[u] != cur) continue;
        for (edge tmp : a[u])
        {
            int v = tmp.node, wei = tmp.weight;
            if (d[v] > cur + wei)
            {

                d[v] = cur + wei;
                pq.push({v, d[v]});
            }
        }
    }
    if (d[fin] == 1e18) d[fin] = -1;
    cout << d[fin];
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    while (m--)
    {
        int x, y;
        long long w;
        cin >> x >> y >> w;
        a[x].push_back({y, w});
    }
    cin >> st >> fin;
    dijk();
}
