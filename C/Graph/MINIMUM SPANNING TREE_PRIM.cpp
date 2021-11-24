#include<bits/stdc++.h>

using namespace std;

const int MAXX= 1e5+1 , oo = 1e9 ;
int n,m ;
int u , v , w ;

typedef pair<int,int> pii ;
vector<pii> adjacence[MAXX] ;
map < pii , int > weight ;
set< pair<pii,int> > mst_res ;

queue< int > VT ;
queue< pii > ET ;
int d[MAXX] , near[MAXX] ;

void input()
{
    cin >> n >> m ;
    for( int i=1 ; i<=n ; i++ )
    {
        for( int j=i ; j<=n ; j++ )
        {
            if( i==j ) weight[pii(i,i)] = 0 ;
            else
            {
                weight[pii(i,j)] = weight[pii(j,i)] = oo ;
            }
        }
    }
    for( int i=0 ; i<m ; i++ )
    {
        cin >> u >> v >> w ;
        adjacence[u].push_back( pii( w,v ) ) ;
        adjacence[v].push_back( pii( w,u ) ) ;
        cout << "weight[pii(" << u << "," << v << ") = " << weight[pii(u,v)] << endl ;
        weight[ pii(u,v) ] = w ;
        weight[ pii(v,u) ] = w ;
    }

}

int PRIM( int node )
{
    cout << "node = " << node << endl << endl;
    int total_d = 0 , d[MAXX] , near[MAXX] ;
    for( int i=1 ; i<=n ; i++ )
    {
        d[i] = weight[ pii(i,node) ] ;
        near[i] = node ;
    }

    d[node] = 0 ;
    priority_queue<pii> V_T ;
    V_T.push( pii( 0,node ) ) ;

    while( V_T.size() )
    {
        pii selected_node = V_T.top() ; V_T.pop() ;
        int s = selected_node.second , d_s = 0-(selected_node.first) ;
        if( d[s] != 0 )
        {
            cout << "__________________________\n updated mst:\n" ;
            cout << s << "-" << near[s] << " ~ " << d[s] << "\n__________________________\n" ;
            mst_res.insert( make_pair( pii(s,near[s]) , d[s] ) ) ;
        }

        if( d_s != d[s] ) continue ;

        total_d += d[s] ;
        d[s] = 0 ;

        for( int i=0 ; i<adjacence[s].size() ; i++ )
        {
            pii x = adjacence[s][i] ;
            cout << "with d[" << adjacence[s][i].second << "] = " << d[x.second] << " and " << "x.first = " << x.first << endl ;
            cout << "checking node #" << adjacence[s][i].second << "(" << adjacence[s][i].first << ")" << endl ;
            if( d[x.second] > x.first )
            {
                d[x.second] = x.first ;

                V_T.push( pii( -d[x.second] , x.second ) ) ;
                near[x.second] = s ;
            }
        }


    }

    return total_d ;
}

void solve()
{
    cout << PRIM(1) << endl ;
    for( auto x = mst_res.begin(); x != mst_res.end(); x++ )
    {
        cout << ((*x).first).first << "-" << ((*x).first).second << " ~~~ " << (*x).second << endl ;
    }

}

int main()
{
    ios_base::sync_with_stdio(false) ;
    cin.tie(0) ;
    input() ;
    solve() ;
}

/*
5 9
1 6 3
1 3 7
6 3 5
6 2 4
6 4 1
3 4 8
2 4 9
2 5 6
4 5 2
*/
