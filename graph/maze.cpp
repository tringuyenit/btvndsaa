#include <bits/stdc++.h>
using namespace std;

#define N 1000
#define pii pair<int,int>

int A[N][N];
int n, m;
int start_row, start_col;
bool found;
bool visited[N][N];
int ans;

void input(){
    cin >> n >> m >> start_row >> start_col;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> A[i][j];
        }
    }
}

bool finalState(pii s){
    if(s.first < 1 || s.first > n || s.second < 1 || s.second > m){
        return true;
    }
    return false;
}

bool legalState(pii s){
    return A[s.first][s.second] == 0 && !visited[s.first][s.second];
}

int main(){
    input();
    
    for(int i = 1; i<=n; i++){
        for(int j = 1; j <= m; j++){
            visited[i][j] = false;
        }
    }
    
    queue<pii> Q;
    map<pii, int> step;

    pii is = make_pair(start_row, start_col);
    step[is] = 0;
    Q.push(make_pair(start_row, start_col));
    while (!found){
        pii s = Q.front();
        Q.pop();

        // move up
        pii ns = make_pair(s.first-1, s.second);
        if(finalState(ns)){
            ans = step[s] + 1;
            found = true;
            break;
        }

        if(legalState(ns)){
            visited[ns.first][ns.second] = true;
            step[ns] = step[s] + 1;
            Q.push(ns);
        }

        // move down
        ns = make_pair(s.first+1, s.second);
        if(finalState(ns)){
            ans = step[s] + 1;
            found = true;
            break;
        }

        if(legalState(ns)){
            visited[ns.first][ns.second] = true;
            step[ns] = step[s] + 1;
            Q.push(ns);
        }

        // move left
        ns = make_pair(s.first, s.second+1);
        if(finalState(ns)){
            ans = step[s] + 1;
            found = true;
            break;
        }

        if(legalState(ns)){
            visited[ns.first][ns.second] = true;
            step[ns] = step[s] + 1;
            Q.push(ns);
        }

        // move right
        ns = make_pair(s.first, s.second-1);
        if(finalState(ns)){
            ans = step[s] + 1;
            found = true;
            break;
        }

        if(legalState(ns)){
            visited[ns.first][ns.second] = true;
            step[ns] = step[s] + 1;
            Q.push(ns);
        }

    }

    cout << ans;
    
    return 0;
}
