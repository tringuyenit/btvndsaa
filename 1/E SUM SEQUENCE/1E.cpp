#include <bits/stdc++.h>
using namespace std;

int main() {
    long size;
    scanf("%li", &size);

    unsigned long long sum = 0;
    unsigned long long input;

    for(long i = 1; i <= size; i++){
        scanf("%llu", &input);
        sum += input;
    }
    
    cout << sum % 1000000007;
    return 0; 
}