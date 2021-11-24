#include <stdio.h>
#include <iostream>
#define MAX_N 101
#define MAX_M 501
#define P 1000000007
using namespace std;

int n;
int M;
int a[MAX_N];
int S[MAX_N][MAX_M];

long long addmod(long long a, long long b){
    a = a%P;
    b = b%P;
    long long tmp = P - b;
    if(tmp > a) return a + b;
    else return a - tmp;
}

void solve(){
    for(int k = 1; k <= M; k++)
        if(k%a[1] == 0)
            S[1][k] = 1;
        else S[1][k] = 0;
    for(int i = 2; i <= n; i++){
        for(int k = 1; k <= M; k++){
            S[i][k] = 0;
            int ub = 0;
            for(int j = 1; j <= i-1; j++) ub += a[j];
            ub = (k-ub)/a[i];
            for(int v = 1; v <= ub; v++)
                if(k - a[i]*v >0)
                    S[i][k] = addmod(S[i][k],S[i-1][k - a[i]*v]);
        }
    }
    cout << S[n][M];
}

void input(){
    scanf("%d%d",&n,&M);
    for(int i = 1; i <= n; i++)
        scanf("%d",&a[i]);
}

int main(){
    input();
    solve();
}
