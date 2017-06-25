#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#define MAXN 10010
#define L(rt) (rt << 1)
#define R(rt) (rt << 1 | 1)
using namespace std;

int dp[25][25];

int main()
{
	char s[25];
	while(cin>>s)
	{
		memset(dp,0,sizeof(dp));
		dp[0][0] = 1;
		int n = strlen(s);
		if(n == 1 || s[0] == '-')
		{
			cout<<0<<endl;
			continue;
		}
		for(int i = 1;i <= n;i ++)
		{
			if(s[i - 1] == '+')
			{
				for(int j = 1;j <= i;j ++)
				{
					dp[i][j] += dp[i - 1][j - 1];
					dp[i][j] += dp[i - 1][j] * j;
				}
			}
			else
			{
				for(int j = 1;j <= i;j ++)
				{
					dp[i][j - 1] += dp[i - 1][j] * j * j;
					dp[i][j] += dp[i - 1][j] * j;
				}
			}
		}
		cout<<dp[n][0]<<endl;
	}
}
