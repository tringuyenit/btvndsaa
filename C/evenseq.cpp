#include <bits/stdc++.h>

using namespace std;
const int N=1e5+1;
int n,a[N],t=0;
int ans=-1e6,S[N];

void input(){
    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> a[i];
    }
}

int evensub(){
    int t;
    int cnt=0;
    for (int i=1;i<=n;i++){
        t=0;
        if (a[i]%2!=0) cnt++;
        if (cnt%2==0){
        for (int j=i;j>=1;j--){
            t+=a[j];
            if (t>ans && t%2==0) ans=t;
        }
        }
        else continue;
    }
    return ans;
}

int main(){
    input();
    cout << evensub() << endl;
}
