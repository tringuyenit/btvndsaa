#include <bits/stdc++.h>
using namespace std;
const int N=1e6+1;
int a[N];
int S[N];
int L1,L2,n,ans;

void input(){
    cin >> n >> L1 >> L2;
    for (int i=1;i<=n;i++)
        cin >> a[i];
}
int solve(){
    deque<int> Q;
    for (int i=1;i<=n;i++){
        /*S[i]=a[i];
        for (int j=i-L2;j<=i-L1;j++){
            if (j>=1 && S[i]<S[j]+a[i])          //GOLD MINE THUONG
                S[i]=S[j]+a[i];
        }
        */
        while (!Q.empty() && Q.front()<i-L2) Q.pop_front();
        if (i-L1>=1){
            while (!Q.empty() && S[Q.back()]<S[i-L1]) Q.pop_back();
            Q.push_back(i-L1);
        }
        S[i]=(Q.empty()?0:S[Q.front()])+a[i];
        ans=max(ans,S[i]);
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ans=0;
    input();
    cout << solve() << endl;
}
