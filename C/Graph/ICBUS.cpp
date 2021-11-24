#include <bits/stdc++.h>
using namespace std;
const int N  = 5001;
vector<int> A[N];
int c[N],d[N];
int n,K;
int dis[N][N];
int minCost[N];// minCost[v] is the minCost for reaching node v from source node s
bool used[N];// used[v] = true means that node v has been fixed (found minCost to v)
void input(){
    cin >> n >> K;
    for(int v = 1; v <= n; v++)
        cin >> c[v] >> d[v];
    for(int i = 1; i <= K; i++){
        int u,v;
        cin >> u >> v;
        A[u].push_back(v);
        A[v].push_back(u);
    }
}
int solve(){
    // compute distance from each node to other nodes
    for(int s = 1; s <= n; s++){
        queue<int> Q;
        for(int v = 1; v <= n; v++) dis[s][v] = n+1;
        dis[s][s] = 0;
        Q.push(s);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = 0; i < A[u].size(); i++){
                int v =A[u][i];
                if(dis[s][v] == n+1){// not visited
                    dis[s][v] = dis[s][u] + 1;
                    Q.push(v);
                }
            }
        }
    }
    // dijkstra not using priority queue
    for(int v= 1; v <= n; v++) minCost[v] = 1e9;
    minCost[1] = 0;
    memset(used,false,sizeof(used));
    for(int i = 1; i <= n; i++){
        int minId = -1;// luu dinh co minCost nho nhat ma chua duoc fixed (used = false)
        int minValue = 1e9;
        for(int v = 1; v <= n; v++) if(!used[v]){
            if(minCost[v] < minValue){
                minValue = minCost[v]; minId = v;
            }
        }
        used[minId] = true;
        if(minId == n){
            cout << minCost[minId]; return 0;
        }
        // update minCost of other not used nodes
        for(int v = 1; v <= n; v++) if(!used[v] && dis[minId][v] <= d[minId]){
            minCost[v] = min(minCost[v],minCost[minId] + c[minId]);
            //cout << "update minCost[" << v << "] = " << minCost[v] << endl;
        }
    }
}
int main(){
    input();
    solve();
}
