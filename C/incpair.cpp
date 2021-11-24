#include <bits/stdc++.h>

using namespace std;

const int N=1001;
int n,a[N],cnt;
int main(){
    cnt=0;
    cin >> n;
    for (int i=1;i<=n;i++)
        cin >> a[i];
    for (int i=1;i<=n-1;i++){
        for (int j=i+1;j<=n;j++){
            if (a[i]<a[j]) cnt++;
        }
    }
    cout << cnt << endl;
}
