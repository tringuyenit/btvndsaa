#include<bits/stdc++.h>

using namespace std ;

int n ;
string str ;

void solve()
{
    string res = "" , temp ;
    int l=str.length() ,l2 ;
    if( l>10 )
    {
        l2=l-2 ;
        while( l2>0 )
        {
            temp += l2%10+'0' ;
            l2/=10 ;
        }
        reverse( temp.begin() , temp.end() ) ;
        res += ( str[0] + temp + str[l-1] ) ;
        cout << res << endl ;
    }
    else
        cout << str << endl ;
}

void input()
{
    cin >> n ;
    for( int i=0 ; i<n ; i++ )
    {
        cin >> str ;
        solve() ;
    }
}

int main()
{
    input() ;
}
