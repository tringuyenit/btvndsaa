#include <bits/stdc++.h>

using namespace std;
const int MOD=1000000007;
const int N=31;
int n,b,a[N];
int func;
unsigned long long cnt=0;

void input(){
    cin >> n >> b;
    for (int i=1;i<=n;i++) cin >> a[i];
}

void solution(){
    if (func==b) cnt++;
}

void TRY(int k){
    for(int v =0; v <= 1; v++){
            if (v==0) func = func - a[k];
            else func=func+a[k];
            if(k == n) solution();
            else{
                    TRY(k+1);
            }
            if (v==0) func = func +a[k];
            else func=func-a[k];
    }
}

int main(){
    input();
    func=a[1];
    TRY(2);
    cout << cnt%MOD << endl;
}
