#include <bits/stdc++.h>

using namespace std;

const int N=1000001;
int a[N];
int n;
int S[N];
int ans;

void input(){
    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> a[i];
    }
}

int maxsub(){

    S[1]=a[1];
    ans=S[1];
    for (int i=2;i<=n;i++){
        if (S[i-1]>0){
            S[i]=S[i-1]+a[i];
        }
        else {
            S[i]=a[i];
        }
        ans=max(ans,S[i]);
    }
    return ans;
}

int main(){
    input();
    cout << maxsub() << endl;
}
