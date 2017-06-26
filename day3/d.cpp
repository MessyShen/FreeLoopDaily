#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<ctype.h>
#include<math.h>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<bitset>
#include<algorithm>
#include<time.h>
using namespace std;

const int N = 60;

int n,m;

double dp[N][N][N*N];

int main() {
    int t;
    scanf("%d",&t);
    while(t --)
    {
        scanf("%d%d",&n,&m);
        memset(dp,0,sizeof(dp));
        dp[0][0][0] = 1;
        for(int i = 1;i <= n;i ++)
        {
            for(int j = 1;j <= m;j ++)
            {
                for(int k = 1;k <= n * m;k ++)
                {
                    if(i == n && j == m)
                    {
                        dp[i][j][k] = (dp[i - 1][j][k - 1] * (n - i + 1) * j + dp[i][j - 1][k - 1] * (m - j + 1) * i + dp[i - 1][j - 1][k - 1] * (n - i + 1) * (m - j + 1)) / (n * m - k + 1);
                    }
                    else
					{
                        dp[i][j][k] = (dp[i - 1][j][k - 1] * (n - i + 1) * j + dp[i][j - 1][k - 1] * (m - j + 1) * i + dp[i - 1][j - 1][k - 1] * (n - i + 1) * (m - j + 1) + dp[i][j][k - 1] * (i * j - k + 1)) / (n * m - k + 1);
                    }
                }
            }
        }
        double ans = 0;
        for(int i = 1;i <= m * n;i ++)
        {
            ans += dp[n][m][i] * i;
        }
        printf("%.10f\n",ans);
    }
}


