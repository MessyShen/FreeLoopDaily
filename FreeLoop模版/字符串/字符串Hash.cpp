/**************************************************

【字符串哈希】
***************************************************
HDU 4090 GemAnd Prince
Problem
每次消灭一片相同颜色的格子，上层的格子往下落，如果左边有整列空格，整体左移，求不能移动时的最大得分。
Input
3 3 3
1 1 3
1 2 1
1 1 2

5 4 3
2 2 3 3
1 1 3 3
3 2 2 2
3 1 1 1
3 1 2 2
Output
36
103

**************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define mp(a, b) make_pair(a, b)
#define pb(a) push_back(a)
typedef unsigned long long ul;
const int N=8, maxn=200010, _hash=10007, seed=13331;

int ans, dd[8][2]={-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};
struct hashmap
{
	int cur, fir[_hash], nxt[maxn], f[maxn];
	ul st[maxn];
	void init()
	{
		cur=0;
		memset(fir, 0, sizeof fir);
		return ;
	}
	int find(ul val, int ans)
	{
		int u=val%_hash;//对质数取模
		for(int i=fir[u]; i; i=nxt[i]) if(val==st[i])
		{
			return ans>f[i] ? 1 : -1;//根据题目具体要求返回值
		}
		return 0;
	}
	void insert(ul val, int ans)
	{
		int u=val%_hash;
		for(int i=fir[u]; i; i=nxt[i]) if(val==st[i])
		{
			f[i]=ans;
			return ;
		}

		st[++cur]=val, nxt[cur]=fir[u], fir[u]=cur, f[cur]=ans;//不存在则插入新节点
		return ;
	}
}H;
struct maze
{
	int n, m, ans, tot, a[N][N], w[N][N];
	vector<pair<int, int> > vec[N*N];
	maze()
	{
		n=m=0;
		memset(a, 0, sizeof a);
	}
	ul hash()//返回字符串的hash值
	{
		ul ret=0;
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				ret=ret*seed+a[i][j]+1;
		return ret;
	}
	bool operator <(const maze&t)const
	{
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				if(a[i][j]!=t.a[i][j])
					return a[i][j]<t.a[i][j];
		return false;
	}
	void read(int _n, int _m)
	{
		n=_n, m=_m;
		memset(a, 0, sizeof a);

		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				scanf("%d", &a[i][j]);
		return ;
	}
	void dfs(int x, int y)
	{
		w[x][y]=tot;
		vec[tot].pb(mp(x, y));
		for(int i=0, tx, ty; i<8; i++)
		{
			tx=x+dd[i][0], ty=y+dd[i][1];
			if(tx<0 || tx>=n || ty<0 || ty>=m)	continue;
			if(a[tx][ty]==a[x][y] && !w[tx][ty])	dfs(tx, ty);
		}
		return ;
	}
	void build()
	{
		tot=0;
		memset(w, 0, sizeof w);
		for(int i=0; i<N*N; i++)	vec[i].clear();
		
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++) if(a[i][j] && !w[i][j])
			{
				++tot;
				dfs(i, j);
			}
		return ;
	}
	void down()
	{
		for(int j=0; j<m; j++)
		{
			int i1=n-1, i2=n-1;
			while(i1>=0 && a[i1][j])	--i1;

			i2=i1;
			while(i2>=0 && i1>=0)
			{
				while(i2>=0 && !a[i2][j])	--i2;
				if(i2>=0) a[i1--][j]=a[i2][j], a[i2--][j]=0;
			}
		}
		return ;
	}
	bool col_empty(int j)
	{
		for(int i=0; i<n; i++)	if(a[i][j])	return false;
		return true;
	}
	void col_copy(int to, int fr)
	{
		for(int i=0; i<n; i++) a[i][to]=a[i][fr], a[i][fr]=0;
		return ;
	}
	void left()
	{
		int j1=0, j2=0;
		while(j1<m && !col_empty(j1))	++j1;
		
		j2=j1;
		while(j1<m && j2<m)
		{
			while(j2<m && col_empty(j2))	++j2;
			if(j2<m)	col_copy(j1++, j2++);
		}
		return ;
	}
	bool ok()
	{
		for(int i=1; i<=tot; i++)	if(vec[i].size()>=3)	return true;
		return false;
	}
	void clear(int i)
	{
		int len=vec[i].size();
		for(int j=0; j<len; j++)
		{
			int x=vec[i][j].first, y=vec[i][j].second;
			a[x][y]=w[x][y]=0;
		}
		ans+=len*len;
		return ;
	}
}ch;

void Dfs(maze a)
{
	H.insert(a.hash(), a.ans);	

	if(!a.ok())
	{
		ans=max(ans, a.ans);
		return ;
	}
	
	for(int i=1; i<=a.tot; i++) if(a.vec[i].size()>=3)
	{
		maze b=a;

		b.clear(i);
		b.down(), b.left(), b.build();
		
		if(H.find(b.hash(), b.ans)>=0)	Dfs(b);
	}
	return ;
}

int main()
{
	int n, m, k;
	while(scanf("%d%d%d", &n, &m, &k)!=EOF)
	{
		ans=0, H.init();

		ch.read(n, m);
		ch.down(), ch.left(), ch.build();

		Dfs(ch);
		printf("%d\n", ans);
	}
	return 0;
}
