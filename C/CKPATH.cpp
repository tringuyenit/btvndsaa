#include <bits/stdc++.h>

using namespace std;
const int N=1e5+1;
int n,m,k,t,cnt;
int p[N];
vector <int> edge[N];
int mark[N];

int main(){
    cin >> t;
    while (t--){
        if (t==-1) break;
        cin >> n >>  m;
        cnt=0;
        for (int i=1;i<=n;i++){
            mark[i]=0;
            while (!edge[i].empty()){
                edge[i].pop_back();
            }
        }
        for (int i=0;i<m;i++){
            int a,b;
            cin >> a >> b;
            edge[a].push_back(b);
            edge[b].push_back(a);
        }
        cin >> k >> p[0];
        mark[p[0]]=1;
        for (int i=1;i<k;i++){
            p[i]=0;
            cin >> p[i];
            for (int j=0;j<edge[p[i-1]].size();j++){
                if (p[i]==edge[p[i-1]][j] && mark[p[i]]!=1){
                    cnt++;
                    mark[p[i]]=1;
                }
            }

        }
        if (cnt==k-1){
                cout << "1" << endl;
            }
        else {
                cout << "0" << endl;
        }
    }
    return 0;
}
