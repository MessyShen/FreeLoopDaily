#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=50+10;

int T, n, m;

int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &n, &m);

		int sn=0, sm=0;
		for(int i=1, x; i<n; i++)
		{
			scanf("%d", &x);
			sn+=x;
		}
		for(int i=0, x; i<m; i++)
		{
			scanf("%d", &x);
			sm+=x;
		}

		int mn=ceil(1.0*sm/m), mx=floor(1.0*sn/(n-1));
		if(sm%m==0)	++mn;
		if(sn%(n-1)==0)	--mx;
		printf("%d %d\n", mn, mx);
	}
	return 0;
}
