#include <bits/stdc++.h>
using namespace std;

int main(){
    stack<int> S;
    for(int i = 1; i <= 10; i++){
        S.push(i);
    }

    while(!S.empty()){
        int v = S.top();
        S.pop();
        cout<<"Stack pop" << v << endl;
    }

    queue<int> Q;
    for(int i = 1; i <= 10; i++){
        Q.push(i);
    }

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        cout<<"Queue pop" << v << endl;
    }
    return 0;
}
