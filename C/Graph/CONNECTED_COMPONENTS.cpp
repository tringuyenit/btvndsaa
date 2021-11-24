#include<bits/stdc++.h>

using namespace std;

const int maxm = 1e7+1 ;
int n,m;
int node1,node2 ;
vector<int> adjacent[maxm] ;

int p[maxm] ;
char color[maxm] ;
int ncc ; // number of connected components
set<int> connected_component[maxm] ;

void input()
{
    cin >> n >> m ;
    for( int i=0 ; i<m ; i++ )
    {
        cin >> node1 >> node2 ;
        adjacent[node1].push_back(node2) ;
        adjacent[node2].push_back(node1) ;
    }
}

void DFS( int u )
{
    color[u] = 'g' ;
    for( int i=0 ; i<adjacent[u].size() ; i++ )
    {
        int v = adjacent[u][i] ;
        if( color[v] == 'w' )
        {
            connected_component[ncc].insert(v) ;
            DFS(v) ;
        }
    }
}

void DFS_general()
{
    for( int v=1 ; v<=n ; v++ )
    {
        color[v] = 'w' ;
    }
    ncc=0 ;
    for( int v=1 ; v<=n ; v++ )
    {
        if( color[v] == 'w' )
        {
            ncc++ ;
            connected_component[ncc].insert(v) ;
            DFS(v) ;
        }
    }
}

void solve()
{
    DFS_general() ;
    cout << ncc << endl ;
    for( int i=1 ; i<=ncc ; i++ )
    {
        cout << "connected_component[" << i << "]:\n" ;
        for( set<int>::iterator it = connected_component[i].begin() ; it!=connected_component[i].end() ; it++ )
        {
            cout << *it << " " ;
        }
        cout << endl ;
    }
}

int main()
{
    ios_base::sync_with_stdio(false) ;
    cin.tie(0) ;
    input() ;
    solve() ;
}
