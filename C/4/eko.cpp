#include<bits/stdc++.h>
using namespace std;

#define MAX 1000001
int n, m, a[MAX];
int res, Left, Right;

void input()
{
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a,a+n);
}

bool isvalid()
{
    long long cut = 0;
    int delta;
    for(int i = 0; i < n; i++)
    {
        delta = a[i] - res;
        if(delta > 0) cut += delta;
    }
    if(cut >= m) return true;
    else return false;
}

void solve()
{
    input();
    res = 0;
    Left = a[0];
    Right = a[n-1];
    while (Left < Right-1)
    {
        res = Left + (Right - Left)/2;
        if (isvalid()){
            Left = res;
        }
        else{
            Right = res ;
        }
    }
    res = Right;
    if (!isvalid()) res = Left;
    cout << res << endl;
}

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
