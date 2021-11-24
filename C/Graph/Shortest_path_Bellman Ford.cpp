#include<bits/stdc++.h>

using namespace std ;

const int maxx=1e4+25 , oo = 99999 ;
int n , m , s , t ;
typedef pair<int,int> pii ;

vector< pii > adj[maxx];
int dist[maxx] ;

int res=-1 ;

void input()
{
    int u,v,w ;
    cin >> n >> m ;
    for( int i=0 ; i<m ; i++ )
    {
        cin >> u >> v >> w ;
        adj[u].push_back( pii( w , v ) ) ;
        dist[u] = oo ;
        dist[v] = oo ;
    }
    cin >> s >> t ;
}

void bellman_ford ( int n , int start )
{
    dist[ start ] = 0;

    for ( int i = 0; i < n - 1; i ++)
    {
        for ( int u = 0; u < n ; u ++)
        {
            for ( int j = 0; j < adj [ u ]. size (); j ++)
            {
                int v = adj [ u ][ j ]. second ;
                int w = adj [ u ][ j ]. first ;
                dist [ v ] = min ( dist [ v ] , w + dist [ u ]);
            }
        }
    }
    res = dist[t] ;
}

void solve()
{
    bellman_ford( n , s ) ;
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
