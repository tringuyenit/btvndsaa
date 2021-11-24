#include<bits/stdc++.h>

using namespace std ;

#define NIL -1
const int maxx = 1e5+1 ;
int m,n ;
bool visited[maxx] ;
vector<int> edge[maxx] ;
int num[maxx] , low[maxx] , t ;
int root ;

int children ;
bool check_point[maxx] , check_bridge[maxx] ;
int count_point=0 , count_bridge=0 ;

void DFS(int u, int parent_u) {
    t+=1 ;
    visited[u] = 1 ;
    num[u] = t ;
    low[u] = t ;
    for ( int i=0;i<edge[u].size();i++ )
    {
        int v=edge[u][i] , temp ;

        if( !visited[v] )
        {
            if( u==root )
                children++ ;
            DFS(v,u);

            low[u] = min( low[u] , low[v] ) ;

            // (1) u is root of DFS tree and has two or more chilren.


            // (2) If u is not root and low value of one of its child is more
            // than discovery value of u.
            if (low[v] >= num[u])
            {
                check_point[u] = true;
//                cout << u << endl;
            }


            if( low[v] == num[v] )
            {
 //               cout << u <<"--"<<v << endl ;
                count_bridge++ ;
            }

        }
        else
        {
            if (v != parent_u)
                low[u]  = min(low[u], num[v]);
        }
    }
    t+=1;
}

void DFS_general(){
    for ( int v=1;v<=n;v++ ) {
        visited[v] = 0 ;
    }
    t=0;
    for ( int v=1;v<=n;v++ ) {
        if( visited[v] == 0 ) {
            root = v ;
            children = 0 ;
            DFS(v,-1);
            if( children <=1 ) check_point[v] = false ;
        }
    }
}

void input()
{
    int u,v ;
    cin >> n >> m ;
    for( int i=0 ; i<m ; i++ )
    {
        cin >> u >> v ;
        edge[u].push_back(v) ;
        edge[v].push_back(u) ;
    }
}

void solve()
{
    DFS_general() ;
    for( int i=1 ; i<=n ; i++ )
    {
//        cout << i << " : " ;
 //       cout << num[i] << " " << low[i] << endl ;
        if( check_point[i] )
        {
            count_point++ ;
//            cout << i << endl ;
        }
    }
    cout << count_point << " " << count_bridge << endl ;
}

int main()
{
    ios_base::sync_with_stdio(false) ;
    cin.tie(0) ;
    input() ;
    solve() ;
}

/*
9 11
6 1
6 4
6 3
1 3
3 2
2 8
2 9
8 5
8 9
5 9
9 7
*/
