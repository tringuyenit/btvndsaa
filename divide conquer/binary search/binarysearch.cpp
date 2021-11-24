#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ww;

ww bs(ww x[], ww start, ww end, ww y){
    if (start > end){
        return -1;
    }

    if(start == end){
        if(x[start] == y){
            return start;
        }
        return -1;
    }

    ww m = (start + end)/2;

    if(x[m] == y){
        return m;
    }

    if(x[m] < y){
        return bs(x, m+1, end, y);
    }

    return bs(x, start, m-1, y);
}

int main(){
    ww a[] = {1,2,3,4,5,6,7};
    cout << bs(a,0,sizeof(a)/sizeof(*a), 6);
    return 0;
}
