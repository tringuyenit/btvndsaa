#include <bits/stdc++.h>
using namespace std;

#define N 6
typedef unsigned long long ww;
ww x[N];
ww n, p;
bool mark[N];
ww counting = 0;

vector<pair<ww,ww>> constraint;
bool compare(vector<ww> v1, vector<ww> v2){
    vector<ww> diff;
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),inserter(diff, diff.begin()));
    if(diff.size() == 0){
        return false;
    }
    return true;
}

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

void pr(vector<ww> v){
    for(int i = 0; i<v.size(); i++){
        printf("%hu ", v[i]);
    }
    printf("\n");
}

bool check(ww v, ww i){
    return !mark[v];
}

void solution(){
    printf("(");
    for(ww i=1; i<=n; i++){
        printf("%hu ", x[i]);
    }
    printf(")");
    printf("\n");
    counting++;
}

void Try(ww i){
    for(ww v = 1; v <= n; v++){
        // printf("v = %hu; i = %hu\n", v, i);
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

                // pr(pre1);
                // pr(pre2);
                // printf("v = %hu; i = %hu\n----\n", v, i);

                if(compare2(pre1, pre2)){
                    continue;
                }
            }

            // pr(pre1);
            // pr(pre2);
            // printf("v = %hu; i = %hu\n----\n", v, i);


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