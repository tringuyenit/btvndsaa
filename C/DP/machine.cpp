#include <bits/stdc++.h>

using namespace std;
const int N=2e6+1;
int L[N],R[N];
int n,s,t,ans;

void input(){
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> s >> t;
        L[t]=max(L[t],t-s);
        R[s]=max(R[s],t-s);
    }
}

int solve(){
    for (int i=1;i<N;i++) L[i]=max(L[i],L[i-1]);
    for (int i=N-2;i>=0;i--) R[i]=max(R[i],R[i+1]);
    ans = -1;
    for (int i=0;i<N-1;i++) ans =max(ans,L[i]+R[i+1]);
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i=0;i<N;i++){
        L[i]=0;
        R[i]=0;
    }
    input();
    cout << solve() << endl;
}
