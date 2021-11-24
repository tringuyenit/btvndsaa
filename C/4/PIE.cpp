#include<bits/stdc++.h>

using namespace std ;

#define MAXX 10005
const double pi = acos(-1.0) ;
int t,n,f ;
double r[MAXX] ;
double r1 ;

void solve()
{
    sort( r,r+n ) ;
    double res ;
    double Left=0.0 , Right=r[n-1];
    double mid ;
    int sum = 0 ;
    while( Right-Left > 1e-6 )
    {
        sum = 0 ;
        mid = Left+(Right-Left)/2.0 ;
        for( int i=0 ; i<n ; i++ )
        {
            r1 = r[i] ;
            while( r1>=mid )
            {
                sum++ ;
                r1-=mid ;
            }
        }
        if( sum>=f )
        {
            res=mid ;
            Left=mid ;
        }
        else
        {
            Right=mid ;
        }
    }
    printf( "%.6lf\n", res ) ;
}

int main()
{
    ios_base::sync_with_stdio(false) ;
    cin.tie(0) ;
    cin >> t ;
    while(t--)
    {
        cin >> n >> f ;
        f+=1 ;
        for( int i=0; i<n ; i++ )
        {
            cin >> r[i] ;
            r[i] = r[i]*r[i]*pi ;
        }

        solve() ;
    }
}
/*
Set left bound l = 0,That everyone do not get anything;
    Right boundary r = pie of size maxr,That person will get the whole pie, but the pie is the largest of all the pie

Focus! Divided by the same person from the same pie a pie,

If the maximum volume of each person points to a, then a smaller pie than certainly have to give up. (From others)

The current upper and lower bounds for the mid compromise, calculated "If sub-pie in accordance with the mid size, how many people can be divided to"
(Directly between 0 and the maximum area of ​​the half piece can request)

*/
