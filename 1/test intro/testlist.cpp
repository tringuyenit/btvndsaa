#include <bits/stdc++.h>
using namespace std;

int main(){
    list<unsigned long long> L;
    for(unsigned long long i=1; i<=5; i++){
        L.push_back(i);
    }

    list<unsigned long long>::iterator it;

    for(it = L.begin(); it!=L.end();it++){
        unsigned long long v = *it;
        cout <<v<< endl;
    }

    unsigned long long v = 30;
    it = find(L.begin(), L.end(), v);
    if(it!=L.end()){
        cout<<"FOUND element "<<v<<endl;
    }else{
        cout<<"NOT FOUND element"<<endl;
    }


    L.insert(it, 10);

    cout<<"after insertion"<<endl;
    for(it = L.begin(); it!=L.end(); it++){
        cout<<*it<<" ";
    }
}
