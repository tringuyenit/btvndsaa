#include <bits/stdc++.h>
#define maxC 1000000007
#define maxn
#define Task "FIBWORDS"
#define ulli unsigned long long int
#define pii pair <int, int>
#define pb push_back
#define mp make_pair

using namespace std;

ulli cnt(string p, string str)
{
    ulli cnt = 0;
    for (int i = 0; i+p.length()-1 < str.length(); ++i) {
        if (str.substr(i, p.length()) == p) cnt++;
    }
    return cnt;
}

ulli fibwords(string p, int n)
{
    string Fn[2], En[2];
    ulli P[2], Q[2], S = 1, j;
    ulli M = p.length();

    //Init
    ulli S0 = 0, S1 = 1;
    for (j = 0; j < M; ++j) {
        S = S0 + S1;
        S0 = S1;
        S1 = S;
    }
    En[0] = En[1] = "";
    Fn[0] = "0"; Fn[1] = "1";
    Q[0] = P[0] = Q[1] = P[1] = 0;
    for (ulli i = 1; i <= j/2; ++i) {
        Fn[0] = Fn[1] + Fn[0];
        Fn[1] = Fn[0] + Fn[1];
    }
    if (j % 2) {
        string str = Fn[0];
        Fn[0] = Fn[1];
        Fn[1] = Fn[1] + str;
    }
    En[1] = Fn[0].substr(S-M+1, M-1) + Fn[1].substr(0, M-1);
    En[0] = Fn[1].substr(Fn[1].length()-M+1, M-1) + Fn[0].substr(0, M-1);
    P[0] = cnt(p, Fn[0]); P[1] = cnt(p, Fn[1]);
    Q[0] = cnt(p, En[0]); Q[1] = cnt(p, En[1]);

    //Calculation
    ulli k = 0;
    for (k = 1; k <= (n-j)/2; ++k) {
        P[0] = P[1] + P[0] + Q[0];
        P[1] = P[0] + P[1] + Q[1];
    }
    k--;
    if((j + 2 * k) == n) return P[0];
    if((j + 2 * k + 1) == n) return P[1] ;
}

void solve()
{
    int n, id = 0;
    string p;
    while (cin >> n >> p) {
        cout << "Case " << ++id << ": ";
        cout << fibwords(p, n) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(); cout.tie();
    //freopen(Task".INP", "r", stdin);
    //freopen(Task".OUT", "w", stdout);
    solve();
    return 0;
}
