#include <bits/stdc++.h>

using namespace std;

const int N=201;
int color[N];
int minf1,f1,f2,k;
int n,q,m,s,w2min=INT_MAX;
int c[N],w1[N][N],w2[N][N];
vector <int> edge[N];


void input(){
    cin >> n >> m >> s >> q;
    for (int i=1;i<=m;i++){
        int x,y,z,t;
        cin >> x >> y >> z >> t;
        edge[x].push_back(y);
        edge[y].push_back(x);
        w1[x][y]=z;w1[y][x]=z;
        w2[x][y]=t;w2[y][x]=t;
        w2min=min(w2min,t);
    }
}

void TRYout(int u) {
    color[u] = 0;
    f1-=w1[u][c[u]];
    f2-=w2[u][c[u]];
    c[u]=0;
    k--;
}

void TRYin(int u) {
    color[u] = 1;
    for (int i=0;i<edge[u].size();i++){
        int v=edge[u][i];
        if(color[v] == 0){
            f1+=w1[u][v];
            f2+=w2[u][v];
            c[u]=v;
            k++;
            if (k==s){
                minf1=min(minf1,f1);
            }
            else{
                if (f2+w2min*(s-k+1)<=q)
                    TRYin(v);
                }
            TRYout(v);
            }
        }
}

void TRY(){
    for (int i=1;i<=n;i++){
        color[i]=0;
        c[i]=0;
    }
    for (int u=1;u<=n;u++){
        if (color[u]==0){
            TRYin(u);
        }
    }
}

void solve(){
    minf1=INT_MAX;
    k=0;
    input();
    TRY();
    cout << minf1 << endl;
}

int main(){
    solve();
}
