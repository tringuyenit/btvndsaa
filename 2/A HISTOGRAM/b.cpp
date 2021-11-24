#include<bits/stdc++.h>
using namespace std;
vector <unsigned long> max_areas;

unsigned long getArea(vector <unsigned long> hist){
    unsigned long n = hist.size();
    stack<unsigned long> st;
    unsigned long largest_area = 0;
    unsigned long top;
    unsigned long toparea;
    unsigned long i = 0;
    while (i < n){
        if (st.empty() || hist[st.top()] <= hist[i]){
            st.push(i++);
        }else{
            top = st.top();
            st.pop();
            toparea = hist[top] * (st.empty() ? i :
            i - st.top() - 1);
            if (largest_area < toparea)
            largest_area = toparea;
        }
    }

    while (st.empty() == false){
        top = st.top();
        st.pop();
        toparea = hist[top] * (st.empty() ? i :
        i - st.top() - 1);
        if (largest_area < toparea)
        largest_area = toparea;
    }

    max_areas.push_back(largest_area);
    return largest_area;
}

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

int main(){
    string cases = "6 2 0 1 0 1 0";
    vector <unsigned long> one_case;

    istringstream is( cases );
    unsigned long num;
    while( is >> num ) {
        one_case.push_back(num);
    }

    getMaxArea(one_case);
    max_areas.push_back(10);
    cout<<max_areas[0]<<endl;
    cout << "yo" << endl;
    
    return 0;
}