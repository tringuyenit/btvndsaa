#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;
vector <int> edge[N],edge1[N];
int n,m,cnt=0,t,len;
int color[N],f[N];
int icc[N],x[N];

void input(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i=1;i<=m;i++){
        int a,b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge1[b].push_back(a);
    }
}

void DFS(int u) {
    t+=1;
    color[u] = 1;
    for (int i=0;i<edge[u].size();i++){
        int v=edge[u][i];
        if(color[v] == 0) {
            DFS(v);
        }
    }
    t+=1;
    f[u]=t;
    x[len]=u;
    len++;
}

void DFSin(){
    for (int v=1;v<=n;v++) {
        color[v] = 0;
    }
    t=0;
    for (int v=1;v<=n;v++) {
        if(color[v] == 0) {
            DFS(v);
        }
    }
}

void DFS1(int u) {
    len=0;
    color[u] = 1;
    for (int i=0;i<edge1[u].size();i++){
        int v=edge1[u][i];
        if(color[v] == 0) {
            DFS1(v);
        }
    }
}

void DFSin1(){
    for (int v=1;v<=n;v++) {
        color[v] = 0;
    }
    for (int i=len-1;i>=0;i--) {
        if(color[x[i]] == 0) {
            cnt++;
            DFS1(x[i]);
        }
    }
}

void solve(){
    input();
    DFSin();
    DFSin1();
    cout << cnt << endl;
}

int main(){
    solve();
}
