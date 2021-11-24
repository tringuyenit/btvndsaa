#include <bits/stdc++.h>
using namespace std;

typedef int ww;
const ww N = 100001;
ww x[N];
ww n, C;
void input(){
    scanf("%d%d", &n, &C);
    for(ww i = 1; i<=n; i++){
        scanf("%d", &x[i]);
    }
}

bool P(ww d){
    // return true if a solution of selecting a staff such that min distance between staffs is greater or equal to d

    ww last = 0 - 1e9;
    ww cnt = 0;
    for(ww i = 1; i <= n; i++){
        if(x[i] - last >= d){
            last = x[i];
            cnt += 1;
        } 
    }

    return cnt >= C;
}

void solve(){
    ww ans = 0;
    ww left = 0;
    ww right = 1e9;
    sort(x+1, x+n+1);

    while(left <right-1){
        ww d = (left + right)/2;

        if(P(d) == true){
            left = d;
            ans = max(ans, d);
        }else{
            right = d;
        }
    }

    if(P(right) == true){
        ans = max(ans, right);
    }else{
        ans = max(ans, left);
    }

    cout<<ans<<endl;
}

int main(){
    ww T;
    scanf("%d", &T);
    for(ww t=1; t<=T; t++){
        input();
        solve();
    }
    return 0;
}
