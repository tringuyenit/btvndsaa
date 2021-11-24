#include <bits/stdc++.h>

using namespace std;

const int N=1000;
set<int> S[N];
int m,n;
int T[N][N];
int x[N];
int best;
int load[N];

void input(){
    int k,a,b;
    cin >> m >> n;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            T[i][j]=0;
    for (int i=1;i<=m;i++){
        cin >> k;
        for (int j=1;j<=k;j++){
            cin >> a;
            S[a].insert(i);
        }
    }
    cin >> k;
    for (int i=1;i<=k;i++){

        cin >> a >> b;
        T[a][b]=1;
        T[b][a]=1;
    }
}

void solution(){
    int maxl=0;
    for (int i=1;i<=m;i++)
        if (load[i]>maxl) maxl=load[i];
    if (maxl<best) best=maxl;
}

bool check(int t,int k){
    for (int i=1;i<=k-1;i++)
        if (T[i][k] && t==x[i]) return false;
    return true;
}

void TRY(int k){
    for (set<int>::iterator it=S[k].begin();it!=S[k].end();it++){
        int t=*it;
        if (check(t,k)){
            x[k]=t;
            load[t]++;
            if (k==n) solution();
            else{
                if(load[t]<best)
                    TRY(k+1);
            }
            load[t]--;
        }
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
