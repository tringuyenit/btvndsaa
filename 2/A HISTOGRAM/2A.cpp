#include<bits/stdc++.h>
using namespace std;

vector <unsigned long> max_areas;

void getMaxArea(vector <unsigned long> hist){

    unsigned long n = hist.size();
    stack<unsigned long> s;
 
    unsigned long max_area = 0;
    unsigned long tp;
    unsigned long area_with_top;
    unsigned long i = 0;
    while (i < n){
        if (s.empty() || hist[s.top()] <= hist[i])
            s.push(i++);
        else{
            tp = s.top();
            s.pop();
            area_with_top = hist[tp] * (s.empty() ? i :
                                   i - s.top() - 1);
            if (max_area < area_with_top)
                max_area = area_with_top;
        }
    }
 
    while (s.empty() == false){
        tp = s.top();
        s.pop();
        area_with_top = hist[tp] * (s.empty() ? i :
                                i - s.top() - 1);
 
        if (max_area < area_with_top)
            max_area = area_with_top;
    }

    max_areas.push_back(max_area);
}

void getMaxArea2(vector<unsigned long> heights) {
    stack<unsigned long> increasing_heights;
    unsigned long max_area = 0;

    for (unsigned long i = 0; i <= heights.size();) {
        if (increasing_heights.empty() ||
            (i < heights.size() && heights[i] > heights[increasing_heights.top()])) {
            increasing_heights.emplace(i);
            ++i;
        } else {
            auto h = heights[increasing_heights.top()];
            increasing_heights.pop();
            auto left = increasing_heights.empty() ? -1 : increasing_heights.top();
            max_area = max(max_area, h * (i - left - 1));
        }
    }

    max_areas.push_back(max_area);
}

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
    for(unsigned long i=0;i<n;++i)
        mx_area = max(mx_area,heights[i]*(right[i]-left[i]+1));
    max_areas.push_back(mx_area);
}

int main(){

    string cases;

    while (1){
        vector <unsigned long> one_case;
        getline(cin, cases);

        istringstream is( cases );
        unsigned long num;
        while( is >> num ) {
            one_case.push_back(num);
        }

        if(one_case.size() == 1 && one_case[0] == 0){
            break;
        }

        getMaxArea(one_case);
        one_case.clear();
    }

    for(unsigned long i = 0; i < max_areas.size(); i++){
        cout << max_areas[i] << endl;
    }
    
    return 0;
}