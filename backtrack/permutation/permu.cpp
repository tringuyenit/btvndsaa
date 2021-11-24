#include <bits/stdc++.h>
using namespace std;

#define N 6
typedef unsigned long long ww;
ww x[N];
ww n, p;
ww counting = 0;
bool mark[N];


vector<pair<ww,ww>> constraint;

bool compare2(vector<ww> v1, vector<ww> v2){
    bool tmp = true;
    for(ww i = 0; i <v1.size(); i++){
        for(ww y = 0; y <v2.size(); y++){
            if(v1[i] == v2[y]){
                tmp = false;
                break;
            }
        }
        if(tmp){
            return true;
        }
    }
    return false;
}

bool check(ww v, ww i){
    return !mark[v];
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
            vector<ww> pre1;
            vector<ww> pre2;
            for(ww t=1; t<=p; t++){
                if(constraint[t-1].second == v){
                    pre1.push_back(constraint[t-1].first);
                }
            }

            if(pre1.size() != 0){
                for(ww y=1; y<=i-1; y++){
                    pre2.push_back(x[y]);
                }

                if(compare2(pre1, pre2)){
                    continue;
                }
            }

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
    scanf("%hu", &n);
    for(ww v = 1; v <= n; v++){
            mark[v] = false; 
    }

    scanf("%hu", &p);
    ww a,b;
    for(ww v = 1; v <= p; v++){
        cin >> a >> b;
        constraint.push_back(pair<ww,ww>(a,b));
    }
    
    x[0] = 0;

    Try(1);
    printf("%hu", counting);

    return 0;
}