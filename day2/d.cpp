#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=50+10, INF=0x7f7f7f7f;
typedef long long lint;
const lint mod=1000000007;

lint cnt[maxn];
int n, dis[maxn];
char a[maxn][maxn];
bool vis[maxn];

void SPFA()
{
	queue<int> q;
	memset(vis, 0, sizeof vis);
	memset(dis, 0x7f, sizeof dis);

	vis[0]=true;
	dis[0]=0;
	q.push(0);
	while(!q.empty())
	{
		int u=q.front();

		for(int v=0; v<n; v++) if(a[u][v]!='0' && dis[v]>dis[u]+a[u][v]-'0')
		{
			dis[v]=dis[u]+a[u][v]-'0';
			if(!vis[v])
			{
				vis[v]=true;
				q.push(v);
			}
		}

		q.pop();
		vis[u]=false;
	}
	return ;
}

int main()
{
	while(scanf("%d", &n)!=EOF)
	{
		for(int i=0; i<n; i++)	scanf("%s", a[i]);
		
		SPFA();
		
		memset(cnt, 0, sizeof cnt);
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				if(a[i][j]!='0' && dis[i]+a[i][j]-'0'==dis[j])
					++cnt[j];

		lint ans=1;
		for(int i=1; i<n; i++)	ans=(ans*cnt[i])%mod;
		printf("%lld\n", ans);
	}
	return 0;
}
