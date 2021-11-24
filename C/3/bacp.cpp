#include <bits/stdc++.h>

using namespace std;

const int N=1000;
int load[N];
bool appear[N];
int c[N];
int a[N][N];
int n,m,best;
int x[N];
int h[N];

void input(){
    int u=1;
    cin >> n >> m;
    for (int i=1;i<=n;i++)
        cin >> c[i];
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            cin >> a[i][j];
            if (a[i][j]=1){
                if (!appear[i]){
                    h[u]=i;
                    u++;
                }
                appear[i]=true;
            }
        }
    for (int i=1;i<=n;i++)
        if (!appear[i]) {
            h[u]=i;
            u++;
    }
}

void solution(){
    int maxl=0;
    for (int i=1;i<=m;i++)
        if (load[i]>maxl) maxl=load[i];
    if (maxl<best) best=maxl;
}

void TRY(int k){
    for (int v=1;v<=m;v++){
        x[h[k]]=v;
        load[v]+=c[h[k]];
        if (k==n) solution();
        else{
            if (load[v]<best)
                TRY(k+1);
        }
        load[v]-=c[h[k]];
    }
}

void solve(){
    best=999999;
    for (int i=1;i<=m;i++) load[i]=0;
    TRY(1);
    cout << best << endl;
}

int main(){
    input();
    solve();
}
