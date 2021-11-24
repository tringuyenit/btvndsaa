#include <bits/stdc++.h>
using namespace std;
const int N = 100;
const int INF = 1000000000;
long long c[N][N];
long long cmin;
int x[N];
int n;
int m;
bool appear[N];
long long f;
long long min_f;// represent the minimal distance
void input(){
    cin >> n >> m;
    cmin = INF;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            c[i][j] = INF;

    for(int k = 1; k <= m; k++){
            int i,j;
            long long w;
            cin >> i >> j >> w;
            c[i][j] = w;
            cmin = w < cmin ? w : cmin;
    }
}
void solution(){
    if(f + c[x[n]][x[1]] < min_f){
        min_f = f + c[x[n]][x[1]];
        //cout << "update best " << min_f << endl;
    }
}
void TRY(int k){
    for(int v =1; v <= n; v++){
        if(!appear[v]){
            x[k] = v;
            appear[v] = true;
            f = f + c[x[k-1]][x[k]];
            if(k == n) solution();
            else{
                if(f + cmin*(n-k+1) < min_f)
                    TRY(k+1);
            }
            appear[v] = false;
            f = f - c[x[k-1]][x[k]];
        }

    }
}
void solve(){
    for(int v = 1; v <= n; v++) appear[v] = false;
    f = 0;
    x[1] = 1;
    appear[1] = true;
    min_f = INF;
    TRY(2);
    cout <<  min_f << endl;
}
int main(){
    input();
    solve();
}
