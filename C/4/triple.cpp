#include <bits/stdc++.h>

using namespace std;

int n,q;
int a[5001];
int cnt=0;
int t;

void input(){
    cin >> n >> q;
    for (int i=1;i<=n;i++)
        cin >> a[i];
}

int bsearch(int left,int right,int x){
    if (left>right) return 0;
    if (left==right){
        if (a[left]==x) return 1;
        else return 0;
    }
    int mid;
    mid=(left+right)/2;
    if (a[mid]==x) return 1+bsearch(left,mid-1,x)+bsearch(mid+1,right,x);
    else if (a[mid]<x) return bsearch(mid+1,right,x);
    else return bsearch(left,mid-1,x);
}

void solve(){
    sort(a+1,a+n+1);
    for (int i=1;i<=n-2;i++){
        for (int j=i+1;j<=n-1;j++){
                cnt+=bsearch(j+1,n,q-a[i]-a[j]);
        }
    }
    cout << cnt << endl;
}

int main(){
    input();
    solve();
}
