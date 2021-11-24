#include <bits/stdc++.h>
using namespace std;

// typedef unsigned long long ww;
typedef int ww;
const ww N = 1000000;
ww a[N];
ww n;
ww F[N];
ww ans;

void input(){
    scanf("%d", &n);
    for(ww i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
}

void solve(){
    F[1] = a[1];
    ans = F[1];
    for(ww i = 2; i <= n; i++){
        if(F[i-1] > 0){
            F[i] = F[i - 1] + a[i];
        }else{
            F[i] = a[i];
        }

        if(F[i] > ans){
            ans = F[i];
        }
    }

    // printf("max = %d\n", ans);

}

int main(){
    input();
    solve();
    cout << ans;

    //8
    //3 5 -10 4 6 -2 9 7
    return 0;
}
