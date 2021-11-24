#include <bits/stdc++.h>
using namespace std;

#define N 6
typedef unsigned long long ww;
ww x[N];
ww n;
bool mark[N];
ww A[N][N];
ww counting = 0;


bool check(ww v, ww i){
    if(mark[v] == true){
        return false;
    }

    for(ww j = 1; j<= i-1; j++){
        if(A[v][x[j]] == 1){
            return false;
        }
    }
    return true;
}

void input(){
    cin >> n;
    for(ww i = 1; i<=n; i++){
        for(ww j=1;j<=n;j++){
            A[i][j] = 0;
        }
    }

    ww K;
    cin >> K;
    for(ww k=1;k<=K;k++){
        ww i,j;
        cin >> i >>j;
        A[i][j]=1; //indicate that i must be before j in each solution
    }
}

void solution(){
    for(ww i=1; i<=n; i++){
        printf("%hu ", x[i]);
    }
    printf("\n");
    counting++;
}

void Try(ww i){
    for(ww v = 1; v <= n; v++){
        if(check(v, i)){
            x[i] = v;
            mark[v]= true;
            if(i==n){
                solution();
            }else{
                Try(i+1);
            }
            mark[v] = false;
        }
    }
}

int main(){
    for(ww v = 1; v <= n; v++){
            mark[v] = false; 
    }

    input();
    
    
    x[0] = 0;

    Try(1);
    cout<<counting;

    return 0;
}