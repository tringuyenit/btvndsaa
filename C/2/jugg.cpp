#include<bits/stdc++.h>

using namespace std;
const int MAX=1000;
int a,b,c,none,ntwo;
queue<pair<int,int>> q;
bool visited[MAX][MAX];
map<pair<int,int>,int> d;
pair<int,int> start;
pair<int,int> finally;

void input(){
    cin >> a >> b >> c;
}

bool check(int r,int v){
    return !visited[r][v];
}

void solve(){
    start=pair<int,int>(0,0);
    visited[0][0]=1;
    q.push(start);
    d[start]=0;
    bool found=false;
    while (!q.empty()){
        pair<int,int> s=q.front();
        q.pop();
        for (int i=0;i<8;i++){
            switch (i){
            case 0:
                none=0;ntwo=s.second;break;
            case 1:
                none=s.first;ntwo=0;break;
            case 2:
                none=a;ntwo=s.second;break;
            case 3:
                none=s.first;ntwo=b;break;
            case 4:
                none=0;ntwo=s.second+s.first;break;
            case 5:
                none=s.first+s.second;ntwo=0;break;
            case 6:
                none=s.first-b+s.second;ntwo=b;break;
            case 7:
                none=a;ntwo=s.second-a+s.first;break;
            }
            if (none>a||ntwo>b||none<0||ntwo<0) continue;
            pair<int,int> ns=pair<int,int>(none,ntwo);

            if (check(none,ntwo)){
                visited[none][ntwo]=true;
                q.push(ns);
                d[ns]=d[s]+1;
            }

            if (none==c||ntwo==c){
                finally=ns;
                found=true;
                break;
            }
        }
        if (found) break;
    }
    if (found) cout << d[finally] << endl;
    else cout << -1 << endl;
}

int main(){
    input();
    solve();
}
