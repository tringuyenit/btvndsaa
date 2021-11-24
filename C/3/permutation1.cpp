#include <bits/stdc++.h>
using namespace std;

const int N = 10001;
int n , x[N] , y[N] ;
long long m ;
bool appear[N] , flag ;
int res  ;


void input()
{
    cin >> n >> m;
}

bool check (int a, long long b)
{
    unsigned long long s = 1;
    for (int i = 1; i <= a; i++)
    {
            s = s * i;
    }
    return b>s ;
}

void solution()
{
    res++;
    if( res == m )
    {
        for (int i=1;i<=n;i++)
            cout << x[i] << " ";
        cout << endl;
        flag = true ;
    }
}

void TRY(int k) {
    for (int v=1;v<=n;v++) {
        if (!appear[v]) {
            x[k] = v;
            appear[v] = true;
            if (k==n) solution();
            if( flag ) return ;
            else TRY(k+1);
            appear[v] = false;
        }
    }
}

void solve()
{
    res = 0;
    if(n<=10)
    {
        if ( check(n,m) )
            cout << "-1" << endl ;
    }
    TRY(1) ;
}

int main()
{
    input() ;
    solve() ;
}
