#include <bits/stdc++.h>

using namespace std;

int main(){
    set<int> Y;
    for(int e = 1; e <= 20; e++){
        Y.insert(e);
    }
    for(int e = 1; e <= 20; e++){
        Y.insert(e);
    }

    set<int>::iterator p;
    for(p = Y.begin(); p!=Y.end(); p++){
        int v = *p;
        cout << v <<  " ";
    }

    int v = 200;
    set<int>:: iterator q = Y.find(v);
    if(q != Y.end()){
        cout <<"FOUND "<< v <<endl;
    }else{
        cout << "NOT FOUND" << endl;
    }

    return 0;
}
