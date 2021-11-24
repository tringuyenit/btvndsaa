#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> am,dg; //am, duong aka -/+
int n,k,x,m;

unsigned long long solve(vector<pair<int,int>>a){ // x and m
    sort(a.begin(),a.end()); //sort vector
    unsigned long long d=0;
    for (int i=a.size()-1;i>=0;i--){
        if (a[i].second==0){
            continue;
        }
        int p=a[i].second/k; //full k
        int r=a[i].second%k; // remainder after full k
        d+=2ll*p*a[i].first; // distance full k
        a[i].second=r; // after full k, consider (x, r)
        if (a[i].second>0){
            d+=2ll*a[i].first;
            int re=k-r; // remainder after k-r
            for (int j=i-1;j>=0;j--){
                int num=min(re,a[j].second);
                a[j].second-=num;
                re-=num;
                if (re==0){
                    break;
                }
            }
        }
    }
    return d;
}
void in(){
    cin >> n >> k;
    for (int i=0;i<n;i++){
        cin >> x >> m;
        if (x>=0){
            dg.push_back(pair<int,int>(x,m));
        }
        else{
            am.push_back(pair<int,int>(-x,m));
        }
    }
    cout << solve(dg)+solve(am) << endl; // seperate duong and am solutioin
}

int main(){
    in();
}
