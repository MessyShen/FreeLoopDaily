#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long lint;
const int maxn=3000+10;

int n;
lint f[maxn], dis[maxn], sum[maxn];
struct node
{
	lint x, c;
	bool operator <(const node&t)const
	{
		return x<t.x;
	}
	void clear()
	{
		x=c=0;
		return ;
	}
	void sc()
	{
		scanf("%lld%lld", &x, &c);
		return ;
	}
}p[maxn];

int main()
{
	while(scanf("%d", &n)!=EOF)
	{
		for(int i=1; i<=n; i++)	p[i].sc();
		sort(p+1, p+1+n);

		memset(dis, 0, sizeof dis);
		memset(sum, 0, sizeof sum);
		for(int i=2; i<=n; i++)
		{
			dis[i]=dis[i-1]+p[i].x-p[i-1].x;
			sum[i]=sum[i-1]+dis[i];
		}

		memset(f, 0x7f, sizeof f);
		p[n+1].x=p[n].x, p[n+1].c=0;
		f[1]=p[1].c;
		for(int i=2; i<=n+1; i++)
			for(int j=1; j<i; j++)
			{
				lint tmp=f[j]+p[i].c+sum[i-1]-sum[j]-dis[j]*(i-j-1);
				f[i]=min(f[i], tmp);
			}
		printf("%lld\n", f[n+1]);
	}
	return 0;
}
