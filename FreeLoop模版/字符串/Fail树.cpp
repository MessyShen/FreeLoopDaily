/**************************************************

【Fail树】
若有单词a和b，且b在a中出现过，那b必定是a的某些前缀的后缀。
在AC自动机中，若有前缀x和y，且x的fail指针指向y，则说明y是x的后缀。
那么将fail指针反转得到一棵fail树，此时u节点代表的前缀是它每一个子树节点的后缀。
在fail树中跑一遍DFS序，每插入一个单词a，每个字符节点+1，查询单词b词尾节点的子树区间，则得到a在b中出现过的次数。
在阿狸的打字机这题中，因为题目的特殊性，不用每次从头插入单词也不用每次新建树状数组，只需要新增一个fa指针往回走就行。
***************************************************
LYDSY 2434 阿狸的打字机
Problem
输入一个字符串，出现小写字母加在词尾，出现'B'删除词尾，出现'P'代表生成一个完整单词。对于每一次询问，求单词x在y中出现的次数。
Input
aPaPBbP
3
1 2
1 3
2 3
Output
2
1
0

**************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<cmath>
#include<algorithm>
#define lowbit(x) ((x)&-(x))
using namespace std;
const int maxn=100000+10, N=26;

int n, m, tot, dfn, id[maxn], ans[maxn], l[maxn], r[maxn], a[maxn];
int cur, fir[maxn], nxt[maxn], ver[maxn];
char s[maxn];

struct Trie
{
	int fail, nxt[N], fa;
	void Init(int _f)
	{
		fail=0, fa=_f;
		memset(nxt, 0, sizeof nxt);
		return ;
	}
}tr[maxn];
struct node
{
	int x, y, id;
	void init(int _x, int _y, int _i)
	{
		x=_x, y=_y, id=_i;
		return ;
	}
	bool operator <(const node&t)const
	{
		return y<t.y;
	}
}dt[maxn];

void Build(int rt)
{
	queue<int> q;
	q.push(rt);

	while(!q.empty())
	{
		int now=q.front(), p=0;
		q.pop();

		for(int i=0; i<N; i++)
		{
			if(!tr[now].nxt[i])	tr[now].nxt[i]=tr[tr[now].fail].nxt[i];
			else
			{
				p=tr[now].nxt[i];
				q.push(p);
				if(now)	tr[p].fail=tr[tr[now].fail].nxt[i];
			}
		}
	}
	return ;
}

void Add(int u, int v)
{
	ver[++cur]=v, nxt[cur]=fir[u], fir[u]=cur;
	return ;
}

void Dfs(int u)
{
	l[u]=++dfn;
	for(int i=fir[u]; i; i=nxt[i]) Dfs(ver[i]);
	r[u]=dfn;
	return ;
}

void Update(int x, int val)
{
	for(int i=x; i<=dfn; i+=lowbit(i)) a[i]+=val;
	return ;
}

int Query(int x)
{
	int ans=0;
	for(int i=x; i; i-=lowbit(i)) ans+=a[i];
	return ans;
}

void Read()
{
	n=tot=0;
	tr[0].Init(0);
	for(int i=0, len=strlen(s), p=0; i<len; i++)
	{
		if(s[i]>='a' && s[i]<='z')
		{
			if(!tr[p].nxt[s[i]-'a'])
			{
				tr[++tot].Init(p);
				tr[p].nxt[s[i]-'a']=tot;
			}
			p=tr[p].nxt[s[i]-'a'];
		}
		else if(s[i]=='B') p=tr[p].fa;
		else id[++n]=p;
	}
	Build(0);

	scanf("%d", &m);
	for(int i=1, x, y; i<=m; i++)
	{
		scanf("%d%d", &x, &y);
		dt[i].init(x, y, i);
	}
	sort(dt+1, dt+1+m);
	return ;
}

void Work()
{
	cur=0;
	for(int i=0; i<=tot; i++) fir[i]=0;
	for(int i=1; i<=tot; i++) Add(tr[i].fail, i);

	dfn=0;
	Dfs(0);

	for(int i=0; i<=dfn; i++) a[i]=0;
	for(int i=0, len=strlen(s), p=0, j=1, ret=0; i<len; i++)
	{
		if(s[i]>='a' && s[i]<='z')
		{
			p=tr[p].nxt[s[i]-'a'];
			Update(l[p], 1);
		}
		else if(s[i]=='B')
		{
			Update(l[p], -1);
			p=tr[p].fa;
		}
		else
		{
			++ret;
			while(j<=m && dt[j].y==ret)
			{
				ans[dt[j].id]=Query(r[id[dt[j].x]])-Query(l[id[dt[j].x]]-1);
				j++;
			}
			if(j>m)	break;
		}
	}

	for(int i=1; i<=m; i++) printf("%d\n", ans[i]);
	return ;
}

int main()
{
	while(scanf("%s", s)!=EOF) Read(), Work();
	return 0;
}
