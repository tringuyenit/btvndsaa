#include <bits/stdc++.h>
using namespace std;

int main(){
    double a[6] = {3.3, 4.4, 6.6, 2.2,5.5,1.1};
    cout << "original : ";
    for (int i = 0; i <6; i++){
        cout << a[i] << " ";
        cout << endl;
    }

    sort(a+3, a+6);
    cout << "first sort" <<endl;
    for(int i = 0; i<6; i++){
        cout<<a[i]<<" ";
    }
    cout<< endl;

    cout << "second sort" <<endl;
    sort(a, a+3, greater <double>());
    for(int i = 0; i<6; i++){
        cout<<a[i]<< " ";
    }
    cout<<endl;

    return 0;
}
