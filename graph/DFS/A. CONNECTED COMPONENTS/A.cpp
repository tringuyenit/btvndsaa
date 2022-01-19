#include <bits/stdc++.h>
using namespace std;

const int N = 1e+5;

vector<int> A[N]; // A is list of adjacent nodes to v
int n, m;
char color[N];
int t;
int d[N], f[N], p[N];
int number_of_connected_component;

void input(){
    cin>> n >> m;
    for(int i=1; i <=m; i++){
        int u, v;
        cin >> u >>v;
        A[u].push_back(v);
        A[v].push_back(u);
    }
}

void DFS(int u){
    t+=1;
    color[u] = 'G';
    d[u] = t;
    for(int i = 0; i<A[u].size(); i++){
        int v = A[u][i];
        if(color[v] == 'W'){
            p[v] = u;
            DFS(v);
        }
    }
    t+=1;
    f[u] = t;
    color[u] = 'B';
}

void DFS(){
    for(int v = 1; v<=n; v++){
        color[v] = 'W';
    }

    number_of_connected_component = 0;

    for(int v = 1; v<=n; v++){
        if(color[v] = 'W'){
            number_of_connected_component += 1;
            DFS(v);
        }
    }

    cout << number_of_connected_component;
}

int main(){
    input();
    DFS();
    return 0;
}