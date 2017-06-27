#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
 
double p[150][150];  

double dp[10005][200];  

int id[10005];  

int main()
{
	int n,m;
	while(~scanf("%d",&m))
	{
		m = m * (m - 1) * (m - 2) / 6;
		for(int i = 0;i < m;i ++)
		for(int j = 0;j < m;j ++)
			scanf("%lf",&p[i][j]);
		scanf("%d",&n);
		for(int i = 0;i < n;i ++)
			scanf("%d",&id[i]);
		memset(dp,0,sizeof(dp));
		for(int i = 0;i <= m;i ++)
		{
			dp[0][i] = 1;
		}
		for(int i = 1;i <= n;i ++)
		{
			for(int j = 0;j < m;j ++)
			{
				dp[i][j] = max(dp[i][j],dp[i - 1][j] * p[j][id[i - 1]]);
				dp[i][id[i - 1]] = max(dp[i][id[i - 1]],dp[i-1][j]*p[j][id[i - 1]]);  
			}
		}
		double ans = 0;
		for(int i = 0;i < m;i ++)
		{
			ans = max(dp[n][i],ans);
		}
		printf("%.6f\n",ans);
	}
	return 0;
}
