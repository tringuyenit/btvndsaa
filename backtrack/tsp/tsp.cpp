#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ww;

const ww INF = 1000000000000;
#define N 100
bool mark[N];
ww x[N];
ww n, m;
ww d[N][N];
ww f; // partial travel distance
ww f_min;
ww cmin;

bool check(ww v, ww k){
    return !mark[v];
}

void input(){
    cin >> n >> m;
    cmin = INF;
    for(ww i = 1; i<=n; i++){
        for(ww j=1;j<=n;j++){
            d[i][j] = INF;
        }
    }
    for(ww k=1;k<=m;k++){
        ww i,j,c;
        cin >>i>>j>>c;
        d[i][j]=c; //indicate that i mwwt be before j in each solution
        cmin = c < cmin ? c : cmin;
    }
}

void solution(){
    for(ww i=1; i<=n; i++){
        printf("%hu ", x[i]);
    }
    printf("\n");
}

void updateBest(){
    if(f + d[x[n]][x[1]] < f_min){
        f_min = f + d[x[n]][x[1]];
        //cout << "update best " << min_f << endl;
    }
}

void Try(ww k){
    for(ww v=2; v<=n; v++){
        if(check(v, k)){
            x[k] = v;
            f = f + d[x[k-1]][x[k]];
            mark[v]= true;
            if(k==n){
                updateBest();
            }else{
                if(f + cmin*(n-k+1) < f_min){
                    Try(k+1);
                }
            }
            f = f - d[x[k-1]][x[k]];
            mark[v] = false;
        }
    }
}

int main(){
    input();
    for(ww v=1; v<=n; v++){
        mark[v] = false;
    }
    x[1] = 1;
    mark[1]= true;
    f_min = INF;
    Try(2);
    cout<< f_min;

    return 0;
}