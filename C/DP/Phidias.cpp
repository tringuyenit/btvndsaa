#include <bits/stdc++.h>
using namespace std;
#define MAXN 200
#define MAXS 600

int W, H, N, w[MAXN], h[MAXN];
int dp[MAXS+1][MAXS+1];

int solution( void )
{
  for (int  ww = 1; ww <= W; ++ww)
    for (int  hh = 1; hh <= H; ++hh)
    {
      int res = ww*hh;
      for (int i = 0; i < N; ++i)
        if( w[i] <= ww && h[i] <= hh )
        {
          int v = dp[ww-w[i]][hh] + dp[w[i]][hh-h[i]];
          if ( v < res ) res = v;
          v = dp[ww][hh-h[i]] + dp[ww-w[i]][h[i]];
          if( v < res ) res = v;
        }
      dp[ww][hh] = res;
    }
  return dp[W][H];
}

int main(){
    int i;
    cin >> W >> H >> N;
    for( i = 0; i < N; ++i)
      cin >> w[i] >> h[i];
    cout << solution() << endl;
    return 0;
}
