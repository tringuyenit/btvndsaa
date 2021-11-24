#include <bits/stdc++.h>
using namespace std;

bool match (char o, char c){
    if(o == '(' && c == ')'){
        return true;
    }
    
    if(o == '[' && c == ']'){
        return true;
    }
    
    if(o == '{' && c == '}'){
        return true;
    }
    return false;
}

bool check(string exp){
    stack<char> S;
    for(unsigned short i = 0; i< exp.length(); i++){
        char tmp = exp[i];
        if(tmp == '(' || tmp == '[' || tmp == '{'){
            S.push(tmp);
        }else{
            if(S.empty()){
                return false;
            }else{
                char o = S.top();
                S.pop();
                if(!match(o, tmp)){
                    return false;
                }
            }
        }
    }

    if(S.empty()){
        return true;
    }else{
        return false;
    }
}

int main(){
    vector<bool> tmp;
    unsigned short T, Z;
    cin >> T;
    for(unsigned short t = 1; t <= T; t++){
        string exp;
        cin >> exp;
        tmp.push_back(check(exp));
    }
    for(unsigned short t = 1; t <= T; t++){
        if(tmp[t-1] == true){
            cout<<1<<endl;
        }else{
            cout<<0<<endl;
        }
    }
    return 0;
}