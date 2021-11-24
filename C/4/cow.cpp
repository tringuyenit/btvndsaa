#include <bits/stdc++.h>

using namespace std;

const int N=1000001;
int x[N];
int n,c;

void input(){
    cin >> n >> c;
    for (int j=1;j<=n;j++)
        cin >> x[j];
    sort(x+1,x+n+1);
}

int cunt(int lam){
    int cnt1=0;
    int last=-1000000000;
    for (int j=1;j<=n;j++){
        if (x[j]-last>=lam){
            cnt1++;
            last=x[j];
        }
    }
    return cnt1;
}

int solve(){
    int cnt,lam;
    int L=0;
    int R=x[n]-x[1];
    while (L<R-1){
        lam=(L+R)/2;
        cnt=cunt(lam);
        if (cnt>=c){
            L=lam;
        }
        else{
            R=lam;
        }
    }
    cnt=cunt(R);
    if (cnt==c) return R;
    else return L;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int i=1;i<=t;i++){
        input();
        cout << solve() << endl;
    }
}
