#include<bits/stdc++.h>

using namespace std;
const int MAX=1000;
int a,b,c;
queue<pair<int,int>> q;
bool visited[MAX][MAX]={false};
map<pair<int,int>,int> d;
pair<int,int> start;
pair<int,int> finally;

void input(){
    cin >> a >> b >> c;
}

bool check(int r,int v){
    if (visited[r][v]) return true;
    if (r>a||v>b||r<0||v<0) return false;
}

void solve(){
    start=pair<int,int>(0,0);
    visited[0][0]=true;
    q.push(start);
    d[start]=0;
    int one[6]={0-a,0,0+a,0,0-a,0+b};
    int two[6]={0,0-b,0,0+b,0+a,0-b};
    bool found=false;
    while (!q.empty()){
        pair<int,int> s=q.front();
        q.pop();
        for (int i=0;i<6;i++){
            int none=s.first+one[i];
            int ntwo=s.second+two[i];
            pair<int,int> ns=pair<int,int>(none,ntwo);
            if (check(none,ntwo)){
                q.push(ns);
                visited[none][ntwo]=true;
            }
            else continue;
            if (none==c||ntwo==c){
                finally=ns;
                found=true;
                break;
            }
            d[ns]=d[s]+1;
        }
    }
    if (found) cout << d[finally] << endl;
    else cout << -1 << endl;
}

int main(){
    input();
    solve();
}
