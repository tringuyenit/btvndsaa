#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ww;
const ww P = 1e9+7;
ww exp(ww x, ww N){
    x = x%P;
    if(N == 1){
        return x;
    }

    ww t = exp(x, N/2);
    t = (t*t) % P;
    if (N % 2 == 1){
        t = (t*x) % P;
    }

    return t;
}

int main(){
    ww x, N;
    cin >> x >> N;
    cout << exp(x, N);
    return 0;
}