#include<bits/stdc++.h>

using namespace std ;

#define MAX 1000001
const int N=30 ;
int n , b ;
long long res , f[N+1][MAX] ;

map< int , pair< long , long > > m ;

void input()
{
    cin >> n >> b ;
    for( int i=0 ; i<n ; i++ )
    {
        long a , c ;
        cin >> a >> c ;
        m[i] = make_pair( a , c ) ;
    }
}

void dp()
{
    for( int i=0 ; i<=n ; i++ )
    {
        for( int j=0 ; j<=b ; j++ )
        {
            if( i==0 || j==0 )
                f[i][j]=0 ;
            else if( m[i-1].first <= j )
            {
                f[i][j] = max( f[i-1][j] , m[i-1].second + f[i-1][j-m[i-1].first] );
            }
            else f[i][j] = f[i-1][j] ;
        }

    }
    res = f[n][b] ;
}

void solve()
{
    res = 0 ;
    dp() ;
    cout << res << endl ;
}

int main()
{
    ios_base::sync_with_stdio(false) ;
    input() ;
    solve() ;
}

/*
5 6
4 2
3 2
2 2
1 2
1 4
*/

