#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int MAX = 505;

ll M, K;
ll Left,Right, mid;
ll Page[MAX];
ll Index[MAX];
ll ValidIndex[MAX];

void Update(ll id)
{
    ll sum = 0, t = Index[id];
    for(ll i = Index[id + 1] - 1; i >= t; i--)
    {
        sum += Page[i];
        if(sum == mid)
        {
            Index[id] = i;
            break;
        }else if(sum > mid)
        {
            Index[id] = i + 1;
            break;
        }
    }
}

bool IsValid()
{
    for(int i = 0; i < K; i++)
        Index[i] = i;
    Index[K] = M;
    for(int i = K - 1; i >= 0; i--)
        Update(i);
    if (Index[0] > 0) return false;

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for(int tc=0;tc<T;tc++)
    {
        ll max_page = 0;
        ll sum_page = 0;
        cin >> M >> K;
        for(int i=0;i<M;i++)
        {
            cin >> Page[i];
            if(Page[i] > max_page) max_page = Page[i];
            sum_page += Page[i];
        }
        Left  = max_page;
        Right = sum_page;
        while (Left < Right)
        {
            mid = (Left + Right) / 2;
            if (IsValid())
            {
                Right = mid;
                for(int i = 0; i < K; i++)
                    ValidIndex[i] = Index[i];
            }
            else
            {
                Left = mid + 1;
            }
        }
        for(int i = 0; i < K - 1; i++)
        {
            for(int j = ValidIndex[i]; j < ValidIndex[i+1]; j++)
                cout << Page[j] << " ";
            cout << "/ ";
        }
        for(int i = ValidIndex[K-1]; i < M; i++)
        {
            cout << Page[i];
            if(i == M-1) break;
            cout << " ";
        }
        cout << endl;
    }
    return 0;
}
