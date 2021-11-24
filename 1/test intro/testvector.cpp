#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> L(3, 100);
    cout << L.size()<<endl;

    for(int i = 0; i<L.size(); i++){
        cout<<L[i] << " ";
    }

    cout <<endl;

    for(int e = 1; e <= 10; e++){
        L.push_back(e);
    }

    for(int i =0; i<L.size(); i++){
        cout << L[i] << " ";
    }
}
