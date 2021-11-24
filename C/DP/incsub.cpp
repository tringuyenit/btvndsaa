#include<bits/stdc++.h>
using namespace std;

#define MAX 10005
int a[MAX], b[MAX], S[MAX];
int n, m;
int ans;

void input()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }
}

int solve()
{
    ans = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            int Max = 0;
            if(Max < S[j]) Max = S[j];
            if(b[j] == a[i])
            {
                S[j] = Max + 1;
                continue;
            }
            ans = max(ans, S[i]);
        }
    }
    return ans;
}

int main()
{
    input();
    cout << solve() << endl;
}
