#include<bits/stdc++.h>

using namespace std;

const int MAXX= 1e5+1 ;
int n,m ;
int u[MAXX] , v[MAXX] , w[MAXX] ;
int ET[MAXX] , nET ;
//edgeTree

int r[MAXX] , p[MAXX] ;
long long res ;

void Swap(int i, int j)
{
    swap( u[i] , u[j] ) ;
    swap( v[i] , v[j] ) ;
    swap( w[i] , w[j] ) ;
}

int Partition ( int w[], int low, int high )
{
    // pivot (Element to be placed at right position)
    int pivot = w[high];

    int i = (low - 1) ;  // Index of smaller element

    for ( int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if (w[j] < pivot)
        {
            i++;    // increment index of smaller element
            Swap( i , j ) ;
        }
    }
    Swap( i + 1 , high ) ;
    return (i + 1) ;
}

void quickSort( int w[], int low, int high )
{
    if (low < high)
    {
        /* pi is partitioning index, w[pi] is now
           at right place */
        int pi = Partition(w, low, high);

        quickSort(w, low, pi - 1);  // Before pi
        quickSort(w, pi + 1, high); // After pi
    }
}

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
    for( int i=0 ; i<m ; i++ )
    {
        cin >> u[i] >> v[i] >> w[i] ;
    }
}

void solve()
{
    for( int i=1 ; i<=n ; i++ ) makeSet(i) ;
    quickSort( w , 0 , m-1 ) ;
    /*
    cout << "after QS:\n" ;
    for( int i=0 ; i<m ; i++ )
        cout << u[i] << " " << v[i] << " " << w[i] << endl ;
    */
    res=0 ;
    nET=0 ;
    int count_n=0 ;
    for( int i=0 ; i<m ; i++ )
    {
        int ru=findSet( u[i] ) ;
        int rv=findSet( v[i] ) ;

        if( ru!=rv )
        {
            unify( ru , rv ) ;
            nET++ ;
            ET[nET] = i ;
            res+=w[i] ;
            count_n++ ;
            if( count_n==n-1 ) break;
        }

    }
    cout << res << endl ;
}

int main()
{
    ios_base::sync_with_stdio(false) ;
    cin.tie(0) ;
    input() ;
    solve() ;
}
