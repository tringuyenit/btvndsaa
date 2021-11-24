#include <bits/stdc++.h>
#define maxC 1000000007
#define maxn 1007
#define Task "VLANTERNS"
#define pii pair <int, int>
#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;

int n, l, a[maxn];
double ans = -maxC;

void in()
{
    cin >> n >> l;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
}

void solve()
{
    sort(a+1, a+n+1);
    ans = max(ans, 1.0 * a[1]);
    for (int i = 2; i <= n; ++i)
        ans = max(ans, (1.0 * (a[i] - a[i-1])) / 2);
    ans = max(ans, 1.0 * (l - a[n]));
    printf("%0.10f", ans);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(); cout.tie();
    //freopen(Task".INP", "r", stdin);
    //freopen(Task".OUT", "w", stdout);
	in();
    solve();
    return 0;
}
