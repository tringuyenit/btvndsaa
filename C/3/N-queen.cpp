#include <bits/stdc++.h>
using namespace std;
const int N=25;
int d1[N],d2[N],r[N],c[N][N];
int n,m,cnt;

void TRY(int k) {
    for(int v=1;v<=n;v++){
       if (r[v]==true && d1[k-v+n-1]==true && d2[k+v]==true && c[v][k]==0){
            r[v]=false;
            d1[k-v+n-1]=false;
            d2[k+v]=false;
            if (k==n) {
                cnt++;
            } else
                TRY(k+1);
            r[v]=true;
            d1[k-v+n-1]=true;
            d2[k+v]=true;
        }
    }
}

void solve(){
    n=1;
    while (n!=0){
        cin >> n >> m;
        cnt=0;
        for (int i=1;i<=n;i++)
            r[i]=true;
        for (int i=0;i<=2*n;i++){
            d1[i]=true;
            d2[i]=true;
        }
        for (int i=0;i<=n;i++)
            for (int j=0;j<=n;j++)
                c[i][j]=0;
        for (int i=0;i<m;i++){
            int a,b;
            cin >> a >> b;
            c[a][b]=1;
        }
        TRY(1);
        if (n!=0) cout << cnt << endl;
    }
}

int main(){
    solve();
}
