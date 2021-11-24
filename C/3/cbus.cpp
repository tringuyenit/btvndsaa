#include <bits/stdc++.h>

using namespace std;

const int N=1000;
bool appear[N];
long long minf,f;
int n,q,load,cmin;;
int c[N][N];
int x[N];

bool check(int v){
    if (appear[v]){
        return false;
    }

    if (v<=n){
        if (load>=q){
            return false;
        }
    }else{
        if (!appear[v-n]){
            return false;
        }
    }

    return true;
}

void solution(){
    if (f+c[x[2*n]][0]<minf){
        minf=f+c[x[2*n]][0];
    }
}

void input(){
    cin >> n >> q;
    for (int i=0;i<=2*n;i++){
        for (int j=0;j<=2*n;j++){
            cin >> c[i][j];
            if (c[i][j]<cmin && i!=j){
                cmin=c[i][j];
            }
        }
    }
}

void TRY(int k){
    for (int v=1;v<=2*n;v++){
        if (check(v)){
            x[k]=v;
            appear[v]=true;

            if (v<=n){
                load++;
            }else{
                load--;
            }

            f=f+c[x[k-1]][x[k]];

            if (k==2*n){
                solution();
            }else{
                if (f+cmin*(2*n-k+1)<minf){
                    TRY(k+1);
                }
            }

            appear[v]=false;

            if (v<=n){
                load--;
            }else{
                load++;
            }
            
            f=f-c[x[k-1]][x[k]];
        }
    }
}

void solve(){
    minf=9999999;
    x[0]=0;
    cmin=9999999;
    appear[0]=true;
    load=0;
    input();
    TRY(1);
    cout << minf << endl;
}

int main(){
    solve();
}
