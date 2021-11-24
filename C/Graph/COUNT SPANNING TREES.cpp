#include<bits/stdc++.h>

using namespace std;

const int MAXX= 1e5+1 ;
int n,m ;
int b[MAXX] , e[MAXX] , w[MAXX] ;
int ET[MAXX] , nET ;
//edgeTree

int r[MAXX] , p[MAXX] ;
long long res ;
int x[MAXX] ;

void makeSet( int x )
{
    p[x] = x ;
    r[x] = 0 ;
}

int findSet( int x )
{
    if( x!=p[x] )
    {
        p[x] = findSet( p[x] ) ;
    }
    return p[x] ;
}

void unify( int x , int y )
{
    if( r[x]>r[y] ) p[y] = x ;
    else
    {
        p[x] = y ;
        if( r[x]==r[y] )r[y]++ ;
    }
}

void input()
{
    cin >> n >> m ;
    for( int i=1 ; i<=m ; i++ )
    {
        cin >> b[i] >> e[i] ;
    }
}

bool check_no_cycle( int k , int v )
{
    // selected edges are ( u[x[1]],v[x[1]] ) , ( u[x[2]],v[x[2]] ) ,... , ( u[x[k-1]],v[x[k-1]] )
    // check if edge ( u[v],v[v] ) can be added without creating cycle or not

    for( int i=1 ; i<=n ; i++ ) makeSet(i) ;
    for( int i=1 ; i<=k-1 ; i++ )
    {
        int rb = findSet( b[x[i]] ) ;
        int re = findSet( e[x[i]] ) ;
            unify(rb,re) ;
    }
    return ( findSet(b[v])!=findSet(e[v]) ) ;
}

void TRY( int k )
{
    //tranh truong hop (1,2,3,4) trung vs (2,1,3,4) ,... thi ta dung bien x[] de luu index: x[k-1]<x[k]
    //--> x[k] = x[k-1]+1
    for( int v=x[k-1]+1 ; v<=m ; v++ )
    {
        if(check_no_cycle(k,v))
        {
            x[k] = v ;
            if( k==n-1 ) res++ ;
            else TRY(k+1) ;
        }
    }
}

void solve()
{
    x[0] = 0 ;
    res=0 ;
    TRY(1) ;
    cout << res << endl;
}

int main()
{
    ios_base::sync_with_stdio(false) ;
    cin.tie(0) ;
    input() ;
    solve() ;
}
