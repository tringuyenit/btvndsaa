#include <bits/stdc++.h>
using namespace std;

const int N = 1e+5;

vector<int> A[N]; // A is list of adjacent nodes to v

int n, m;
int d[N]; // d[v] = -1 indicates node has not been visited
void input(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i<=m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        A[u].push_back(v);
        A[v].push_back(u);
    }
}

void init(){
    for(int v=1; v<=n; v++){
        d[v]=-1;
    }
}

bool BFS(int u){
    queue<int> Q;
    Q.push(u);
    d[u]=0;
    while (!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i = 0; i < A[v].size(); i++){
            int x = A[v][i];
            if(d[x]>-1){ // x has been visited, color[X] = GREY
                if((d[v] + d[x]) % 2 == 0 ){
                    return false;
                }
            }else{// x has not been visited, color[x] = WHITE
                d[x] = d[v] + 1;
                Q.push(x);
            }
        }
    }

    return true;
    
}

void solve(){
    init();
    int ans = 1;
    for(int v = 1;  v <= n; v++){
        if(d[v] == -1){
            bool check = BFS(v);
            if(!check){
                ans = 0;
                break;
            }
        }
    }

    cout<<ans;
}

int main(){
    input();
    solve();
    return 0;
}