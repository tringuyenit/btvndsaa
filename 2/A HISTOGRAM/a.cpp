#include<bits/stdc++.h>
using namespace std;
vector <unsigned long> max_areas;
class Solution {
public:
    void getMaxArea3(vector<unsigned long> heights) {
        unsigned long n = heights.size();

        vector<unsigned long> left,right;
        
        stack<unsigned long> mystack;

        for(unsigned long i=0;i<n;++i){
            if(mystack.empty()){
                left[i] = 0;
                mystack.push(i);
            }else{
                while(!mystack.empty() and heights[mystack.top()]>=heights[i]){
                    mystack.pop();
                }          
                left[i] = mystack.empty()?0:mystack.top()+1;
                mystack.push(i);
            }
        }
        
        while(!mystack.empty()){
            mystack.pop();
        }
        
        for(unsigned long i=n-1;i>=0;--i){
            if(mystack.empty()){
                right[i] = n-1;
                mystack.push(i);
            }else{
                while(!mystack.empty() and heights[mystack.top()]>=heights[i]){
                    mystack.pop();
                }
                    
                right[i] = mystack.empty()?n-1:mystack.top()-1;
                mystack.push(i);
            }
        }
        unsigned long mx_area = 0;    //Stores max_area
        for(unsigned long i=0;i<n;++i){
            mx_area = max(mx_area,heights[i]*(right[i]-left[i]+1));
        }
        
        cout << mx_area << endl;
        max_areas.push_back(mx_area);
    }
};

int main(){
    Solution sol;
    string cases;
    int a = 2;

    while (a>=0){
        vector <unsigned long> one_case;
        getline(cin, cases);

        istringstream is( cases );
        unsigned long num;
        while( is >> num ) {
            one_case.push_back(num);
        }

        // if(one_case.size() == 1 && one_case[0] == 0){
        //     break;
        // }

        // getMaxArea3(one_case);

        cout<<cases<<endl;
        a--;

        // sol.getMaxArea3(one_case);
    }
    
    return 0;
}