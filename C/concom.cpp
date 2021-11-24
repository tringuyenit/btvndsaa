#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;
vector <int> edge[N];
int color[N];
int icc[N];
int n,m,cnt=0;

void input(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i=1;i<=m;i++){
        int a,b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}

void DFS(int u) {
    color[u] = 1;
    icc[u]=cnt;
    for (int i=0;i<edge[u].size();i++){
        int v=edge[u][i];
        if(color[v] == 0) {
            DFS(v);
        }
    }
}

int DFSin(){
    for (int v=1;v<=n;v++) {
        color[v] = 0;
    }
    for (int v=1;v<=n;v++) {
        if(color[v] == 0) {
            cnt++;
            DFS(v);
        }
    }
    return cnt;
}

int main(){
    input();
    cout << DFSin() << endl;
    /*for (int i=1;i<=cnt;i++){
        cout << "CC[" << i << "]";
        for (int j=1;j<=n;j++){
            if (icc[j]==i) cout << j << " ";
        }
        cout << endl;
    }*/
}
