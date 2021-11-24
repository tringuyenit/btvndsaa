#include <bits/stdc++.h>
using namespace std;

int main(){
    map<int, int> m;
    for(int i = 1; i <=5; i++){
        m.insert(pair<int, int>(i, 10*i));
    }

    m[6] = 100;

    for (int k = 1; k <= 6; k++){
        cout << "m["<<k<<"]=" << m[k] << endl;
    }

    unordered_map<string, string> m2;
    m2["abc"] = "abcabc";
    m2["xyz"] = "xyzxyz";

    string k = "abc";
    cout << "m1["<<k<<"]=" << m2[k] << endl;

    map<pair<int, int>, int> m3;
    m3[pair<int, int>(2,5)] = 60;
    m3[pair<int, int>(7,10)] = 80;

    cout << "m[2,5]=" << m3[pair<int, int>(2,5)] << endl;
    cout << "m[7,10]=" << m3[pair<int, int>(7,10)] << endl;
    return 0;
}
