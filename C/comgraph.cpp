#include <bits/stdc++.h>

using namespace std;
const int N=1e3+1;
int n,cnt=0;
int a[N][N];

void insol(){
    cin >> n;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cin >> a[i][j];
            if (i==j && a[i][j]!=0){
                cnt=1;
                cout << "0" << endl;
                break;
            }
            else{
                if (i!=j && a[i][j]!=1){
                    cnt=1;
                    cout << "0" << endl;
                    break;
                }
            }
        }
        if (cnt==1) break;
    }
    if (cnt==0)
    cout << "1" << endl;
}

int main(){
    insol();
}
