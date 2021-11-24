#include <bits/stdc++.h>
using namespace std;
// top down version

typedef int ww;
const ww N = 1e4 + 1;
ww X[N], Y[N];
ww n, m;
ww F[N][N];

void input(){
    cin >> n >> m;
    for(ww i = 1; i <= n; i++){
        cin >> X[i];
    }
    for(ww j = 1; j <= m; j++){
        cin >> Y[j];
    }
}

void init(){
    for(ww i = 0; i <= n; i++){
        for(ww j = 0; j <= m; j++){
            F[i][j] = -1;
        }
    }
}

ww lcs(ww i, ww j){
    if(i == 0){
        F[i][j] = 0;
    }else if(j == 0){
        F[i][j] = 0;
    }else{
        if (F[i][j] == -1){
            if(X[i] == Y[j]){
                F[i][j] = 1 + lcs(i-1, j-1);
            }else{
                ww t1 = lcs(i-1, j);
                ww t2 = lcs(i, j-1);
                F[i][j] = max(t1, t2);
            }
        }
    }

    return F[i][j];     
}

void solve(){
    init();
    cout << lcs(n,m);
}

int main(){
    input();
    solve();
    return 0;
}
