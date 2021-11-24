#include <bits/stdc++.h>

using namespace std;

int main(){
unsigned long long n,M,a,b;

    cin >> n >> M;

    a=(((n+1)% M)*((2*n+1)%M)*((2*n+3)%M)) % M;

    cout << a << endl;
}
