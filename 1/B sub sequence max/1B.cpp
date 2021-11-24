#include <bits/stdc++.h>
using namespace std;

int maxSubArraySum(vector<unsigned long long> L)
{
    int max_so_far = INT_MIN, max_ending_here = 0;

    for (int i = 0; i < L.size(); i++)
    {
        max_ending_here = max_ending_here + L[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;

        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}

int main() {
    long size;
    scanf("%li", &size);
    vector<unsigned long long> L;

    unsigned long long input;

    for(long i = 1; i <= size; i++){
        scanf("%llu", &input);
        L.push_back(input);
    }
    
    cout << maxSubArraySum(L);
    return 0; 
}