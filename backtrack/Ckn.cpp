#include <bits/stdc++.h>
using namespace std;

#define N 15
typedef unsigned long long ww;
ww x[N];
ww k, n;

bool check(ww v, ww i){
    return true;
}

void solution(){
    for(ww i=1; i<=k; i++){
        // if(i==k){
        //     printf("%hu", x[i]);
        //     break;
        // }
        printf("%hu ", x[i]);
    }
    printf("\n");
}

void Try(ww i){
    for(ww v = x[i-1]+1; v <= n-k +i; v++){
        if(check(v, i)){
            x[i] = v;
            if(i==k){
                solution();
            }else{
                Try(i+1);
            }
        }
        
    }
}

int main(){
    scanf("%hu %hu", &k, &n);
    x[0] = 0;
    Try(1);
    return 0;
}