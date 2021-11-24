#include <bits/stdc++.h>

using namespace std;

stack<char> st;
int n;
char c;

bool match(char a, char b){
    if (a=='(' && b==')') return true;
    if (a=='[' && b==']') return true;
    if (a=='{' && b=='}') return true;
    return false;
}

void cs(){
    while (!st.empty())
        st.pop();
}

int check(string s){
    cs();
    for (int i=0;i<s.length();i++)
        {
            if (s[i]=='('||s[i]=='['||s[i]=='{')
                st.push(s[i]);
            else
                if (st.empty()) return 0;
                else {
                    c=st.top();st.pop();
                    if (!match(c,s[i])) return 0;
                }
        }
        if (st.empty()) return 1;
        else return 0;
        }
int main(){
    cin >> n;
    for (int j=0;j<n;j++){
        string s;
        cin >> s;
        cout << check(s) << endl;
    }
}
