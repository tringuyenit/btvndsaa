#include<bits/stdc++.h>

using namespace std ;

const int maxx=1e3+25 , oo = 99999 ;
int n , m , s , t ;

int dist[maxx][maxx];
int weight[maxx][maxx];
int res=-1 ;

void input()
{
    int u,v,w ;
    cin >> n >> m ;
    for( int i=1 ; i<=n ; i++ )
    {
        weight[i][i] = 0 ;
        for( int j=i+1 ; j<=n ; j++ )
        {
            weight[i][j] = weight[j][i] = oo ;
        }
    }
    for( int i=0 ; i<m ; i++ )
    {
        cin >> u >> v >> w ;
        weight[u][v] = w ;
    }
    cin >> s >> t ;
}

void floyd_warshall( )
{
    for ( int i = 1; i <= n ; i ++)
    {
        for ( int j = 1; j <= n ; j ++)
        {
            dist [ i ][ j ] = weight[i][j] ;
        }
    }

    for ( int k = 1; k <= n ; k ++)
    {
        for ( int i = 1; i <= n ; i ++)
        {
            for ( int j = 1; j <= n ; j ++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    if( dist[s][t] != '\0' )
        res = dist[s][t] ;
    /*
    cout << "    " ;
    for( int i=1 ; i<=n ; i++ )
        cout << i << "    " ;
    cout << endl ;
    for( int i=1 ; i<=n ; i++ )
    {
        for( int j=1 ; j<=n ; j++ )
        {
            printf( "%5d" , dist[i][j] ) ;
        }
        cout << endl ;
    }
    */
}

void solve()
{
    floyd_warshall() ;
//    cout << s << "-" << t << " = " << dist[s][t] << endl ;
    cout << res << endl ;
}

int main()
{
    ios_base::sync_with_stdio(false) ;
    cin.tie(0) ;

    input() ;
    solve() ;
}
