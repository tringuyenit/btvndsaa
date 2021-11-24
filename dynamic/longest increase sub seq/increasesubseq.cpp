#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ww;
const ww N = 1e4 + 1;
ww a[N];
ww n;
ww F[N];
ww ans;

void input(){
    scanf("%llu", &n);
    for(ww i = 1; i <= n; i++){
        scanf("%llu", &a[i]);
    }
}

void solve(){
    F[1] = 1;
    ans = F[1];
    for(ww i = 2; i <= n; i++){
        F[i] = 1;
        for(ww j = 1; j <= i - 1; j++){
            if(a[i] > a[j]){
                F[i] = max(F[i], F[j] + 1);
            }
            ans = max(F[i], ans);
        }
    }
    printf("%llu", ans);
}

int main(){
    input();
    solve();
    return 0;
}
