#include <bits/stdc++.h>

using namespace std;

const int N=30;
int n,m,cnt;
int b[N],e[N],x[N];
int r[N];
int p[N];
long long rs;

void input(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i=1;i<=m;i++){
        cin >> b[i] >> e[i];
    }
}

void makeset(int x){
    p[x]=x;
    r[x]=0;
}

int findset(int x){
    if (x!=p[x]){
        p[x]=findset(p[x]);
    }
    return p[x];
}

void link(int x,int y){
    if (r[x]>r[y]) p[y]=x;
    else{
        p[x]=y;
        if (r[x]==r[y]) r[y]+=1;
    }
}

bool check(int k,int v){
    for (int i=1;i<=n;i++) makeset(i);
    for (int i=1;i<=k-1;i++){
        int rb=findset(b[x[i]]);
        int re=findset(e[x[i]]);
        link(rb,re);
    }
    return findset(b[v])!=findset(e[v]);
}

void TRY(int k){
    for (int v=x[k-1]+1;v<=m;v++){
        if (check(k,v)){
            x[k]=v;
            if (k==n-1) cnt++;
            else TRY(k+1);
        }
    }
}

void solve(){
    input();
    cnt=0;
    x[0]=0;
    TRY(1);
    cout << cnt << endl;
}

int main(){
    solve();
}
