#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 1000001

long long res ;
int n ;
vector<string> str ;
string temp ;

string findSum(string str1, string str2)
{
    if (str1.length() > str2.length())
        swap(str1, str2);

    string str = "";

    int n1 = str1.length(), n2 = str2.length();

    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }

    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }

    if (carry)
        str.push_back(carry+'0');

    reverse(str.begin(), str.end());
    return str;
}

void input()
{
    cin >> n ;
    for( int i=0 ; i<n ; i++ )
    {
        cin >> temp ;
        str.push_back(temp) ;
    }
}

void solve()
{
    temp = "0" ;
    for( int i=0 ; i<n ; i++ )
        temp = findSum( temp , str[i] ) ;

    for( int i=0 ; i<temp.length() ; i++ )
    {
        res =  (res*10 + ( temp[i]-'0' ))%MOD ;
    }
    cout << res << endl ;
}

int main()
{
    input() ;
    solve() ;
/*
    for( int i=0 ; i<n ; i++ )
        cout << str[i] << endl ;
*/
}
