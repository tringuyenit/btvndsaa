#include<bits/stdc++.h>
using namespace std;
vector <unsigned long> max_areas;

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

int main(){
    vector <unsigned long> data;
    unsigned long number_of_rec;

    while (1){
        scanf("%lu", &number_of_rec);
        if(number_of_rec == 0){
            break;
        }else{
            for(unsigned long i = 1; i<= number_of_rec; i++){
                unsigned long input;
                scanf("%lu", &number_of_rec);
                data.push_back(input);
            }
            getArea(data);
        }
    }

    for(unsigned long i = 0; i<= max_areas.size(); i++){
        cout<<max_areas[i]<<endl;
    }
    
    return 0;
}