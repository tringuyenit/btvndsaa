#include <bits/stdc++.h>
using namespace std;
// bottom up

typedef int ww;
const ww N = 1e4 + 1;
ww X[N];
ww Y[N];
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
        F[i][0] = 0;
    }
    for(ww j = 0; j <= m; j++){
        F[0][j] = 0;
    }
}

void solve(){
    init();
    for(ww i = 1; i <= n; i++){
        for(ww j = 1; j <= m; j++){
            if(X[i] == Y[j]){
                F[i][j] = F[i-1][j-1] +1;
            }else{
                if(F[i-1][j] > F[i][j-1]){
                    F[i][j] = F[i-1][j];
                }else{
                    F[i][j] = F[i][j-1];
                }
            }
        }
    }
    cout << F[n][m];
}

int main(){
    input();
    solve();
    return 0;
}
