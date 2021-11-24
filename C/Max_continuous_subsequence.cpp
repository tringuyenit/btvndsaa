#include<bits/stdc++.h>

using namespace std ;

#define MAX 1000001
int n , w[MAX];
int a_end ;
long long res ;

void input()
{
    cin >> n ;
    for( int i=1 ; i<=n ; i++ )
        cin >> w[i] ;
}

void solve()
{
    res = INT_MIN ;
    a_end = 0 ;
    for( int i=1 ; i<=n ; i++ )
    {
        a_end += w[i] ;
        if( res < a_end ) res = a_end ;
        if( a_end < 0 ) a_end = 0 ;
    }
    cout << res << endl ;
}

int main()
{
    input() ;
    solve() ;
}
