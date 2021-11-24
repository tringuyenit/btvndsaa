#include <bits/stdc++.h>
using namespace std;

#define N 20
typedef unsigned long long ww;
ww x[N];
ww n;

bool check(ww v, ww i){
    if(v+x[i-1] > 1){
        return false;
    } // this if statement is for not '11' problem, otherwise remove this if
    return true;
}

void solution(){
    for(ww i=1; i<=n; i++){
        printf("%d", x[i]);
    }
    printf("\n");
}

void Try(ww i){
    for(ww v = 0; v <= 1; v++){
        if(check(v, i)){
            x[i] = v;
            if(i==n){
                solution();
            }else{
                Try(i+1);
            }
        }
        
    }
}

int main(){
    scanf("%d", &n);
    Try(1);
    return 0;
}