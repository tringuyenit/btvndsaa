#include <bits/stdc++.h>

using namespace std;

const int N=1000;
int x[N];
long long countd,n;
bool appear[N];

bool check(int a, int b){
    if (appear[a]) return false;
    if (b<6) return true;
    return (100*x[0]+10*x[1]+x[2]-100*x[3]-62+1000*x[4]+100*x[5]+10*a+x[2]==n);
}
void TRY(int k){
    for (int v=1;v<=9;v++){
        if (check(v,k)){
            appear[v]=true;
            x[k]=v;
            if (k==6) countd++;
            else TRY(k+1);
            appear[v]=false;
        }
    }
}

void input(){
    cin >> n;
}

int main(){
    countd=0;
    input();
    TRY(0);
    cout << countd <<endl;
}
