#include <bits/stdc++.h>

using namespace std;

const int N=10001;
int a[N];
int b[N];
int S[N][N];
int n,m,ans;
char trace[N][N];

void input(){
    cin >> n >> m;
    for (int i=1;i<=n;i++){
        cin >> a[i];
        S[i][0]=0;
    }
    for (int j=1;j<=m;j++){
        cin >> b[j];
        S[0][j]=0;
    }
}

int comsub(){
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++){
            if (a[i]==b[j]){
                S[i][j]=S[i-1][j-1]+1;
                trace[i][j]='D';
            }
            else {
                if (S[i-1][j]>S[i][j-1]){
                    S[i][j]=S[i-1][j];
                    trace[i][j]='U';
                }
                else {
                    S[i][j]=S[i][j-1];
                    trace[i][j]='L';
                }
            }
        }
    return ans;
}

int main(){
    input();
    comsub();
    stack<int> P;
    int i=n,j=m;
    while (i>0 && j>0){
        if (trace[i][j]=='D'){
            P.push(a[i]);
            i=i-1;
            j=j-1;
        }
        else {
            if (trace[i][j]=='U') i=i-1;
            else j=j-1;
        }
    }
    while (!P.empty()){
        cout << P.top() << endl;
        P.pop();
    }
}
