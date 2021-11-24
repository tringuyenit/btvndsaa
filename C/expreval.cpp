#include <bits/stdc++.h>

using namespace std;
const long long mod=1000000009;
const int N=2e5+1;
int n,b[N];
int a[N];
long long t;

int main(){
    cin >> n;
    for (int i=0;i<n;i++) cin >> a[i];
    b[0]=1;
    for (int i=1;i<n;i++){
        cin >> b[i];
        if (b[i]==2) {
            t=(a[i-1]%mod*a[i]%mod)%mod;
            a[i]=t;
            a[i-1]=0;
            b[i]=b[i-1];
        }
    }
    t=a[0];
    for (int i=1;i<n;i++){
        switch (b[i]){
        case 0:
            t=(t-a[i]);
            break;
        case 1:
            t=(t+a[i]);
            break;
        }
    }
    cout << t%mod << endl;
}
