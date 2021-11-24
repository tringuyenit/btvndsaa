#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned long long a;
    unsigned long long b;
    scanf("%llu %llu", &a, &b);

    a = pow(a,b);

    cout << a % 1000000007;
    return 0; 
}