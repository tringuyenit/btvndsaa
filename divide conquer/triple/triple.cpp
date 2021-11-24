#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ww;
ww a[5001];
ww n;
ww K;
ww ans;

void input(){
    cin >> n >> K;
    for(ww i = 1; i <= n; i++){
        cin >> a[i];
    }
}

ww bs(ww x[], ww start, ww end, ww y){
    if (start > end){
        return 0;
    }
    if(start == end){
        // if(x[start] == y){
        //     return start;
        // }
        // return -1;
        if(x[start] == y){
            return 1;
        }
        return 0;
    }

    ww m = (start + end)/2;

    if(x[m] == y){
        return 1 + bs(x, start, m-1, y) + bs(x, m+1, end, y);
    }

    if(x[m] < y){
        return bs(x, m+1, end, y);
    }

    return bs(x, start, m-1, y);
}

void solve(){
    ans = 0;
    // sort(a, a+n); // ?????
    sort(a+1, a+n+1); // ?????
    for(int i = 1; i <= n-2; i++){
        for(int j = i+1; j<= n-1; j++){
            ans = ans + bs(a, j+1, n, K - a[i] - a[j]);
        }
    }
    cout << ans;
}

int main(){
    input();
    solve();
    return 0;
}
