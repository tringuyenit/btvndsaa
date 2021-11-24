#include<bits/stdc++.h>

using namespace std ;

const int maxx = 1e5+25 ;
int n , m ;
int a , b ;
vector<int> adjacent[maxx] ;
bool visited[maxx] , res=1 ;
int color[maxx] ;

void input()
{
    cin >> n >> m ;
    for( int i=0 ; i<m ; i++ )
    {
        cin >> a >> b ;
        adjacent[a].push_back(b) ;
        adjacent[b].push_back(a) ;
    }
}

void BFS( int u )
{
    color[u] = 1 ;
    queue<int> q ;
    q.push( u ) ;
    while( !q.empty() )
    {
        int v = q.front() ; q.pop() ;
        for( int i=0 ; i<adjacent[v].size() ; i++ )
        {
            int x = adjacent[v][i] ;

            if( color[x] == -1 )
            {
                color[x] = 1 - color[v] ;
                q.push(x) ;
            }

            else
            {
                if( color[x] == color[v] )
                    res = 0 ;
            }
        }
    }

}

void BFS_general()
{
    for( int i=1 ; i<=n ; i++ )
    {
        color[i] = -1 ;
    }
    for( int i=1 ; i<=n ; i++ )
    {
        if( color[i]==-1 )
        {
            BFS(i) ;
        }
    }
}

void solve()
{
    BFS_general() ;
/*
    cout << "color: " ;
    for( int i=1 ; i<=n ; i++ )
    {
        cout << color[i] << " " ;
    }
    cout << endl ;
*/
    cout << res << endl ;
}

int main()
{
    ios_base::sync_with_stdio(false) ;
    cin.tie(0) ;

    input() ;
    solve() ;
}
