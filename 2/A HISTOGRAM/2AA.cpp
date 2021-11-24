#include<bits/stdc++.h>
using namespace std;

vector <unsigned long long> max_areas;

void getMaxArea(vector <unsigned long long> hist){

    unsigned long long n = hist.size();
    stack<unsigned long long> s;
 
    unsigned long long max_area = 0;
    unsigned long long tp;
    unsigned long long area_with_top;
    unsigned long long i = 0;
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


int main(){

    string cases;

    while (1){
        vector <unsigned long long> one_case;
        getline(cin, cases);

        istringstream is( cases );
        unsigned long long num;
        is >> num;
        while( is >> num ) {
            one_case.push_back(num);
        }

        if(one_case.size() == 0){
            break;
        }

        getMaxArea(one_case);
        one_case.clear();
    }

    for(unsigned long long i = 0; i < max_areas.size(); i++){
        cout << max_areas[i] << endl;
    }
    
    return 0;
}