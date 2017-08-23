/**************************************************

【Trie图】
***************************************************
CF 455B A Lot of Games
Problem
两个人轮流往初始为空的字符串添加字母，要求添加后的串至少为某个单词的前缀，不能添加则失败。
一共k局游戏，每局的输家为下一局的先手，若想赢得最后一局，应该在初始时选择先手还是后手？
Input
2 3
a
b
3 1
a
b
c
1 2
ab
Output
First
First
Second

**************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=100000+10, N=26;

int n, k, tot;
char s[maxn];
struct Trie
{
	int cnt, win, fail;
	Trie *nxt[N];
	Trie()
	{
		cnt=0, win=0, fail=0;
		for(int i=0; i<N; i++) nxt[i]=NULL;
	}
};

void Insert(Trie *rt, char *ch)
{
	Trie *p=rt;
	if(p==NULL)	return ;
	for(int i=0, m=strlen(ch); i<m; i++)
	{
		if(p->nxt[ch[i]-'a']==NULL)
		{
			p->nxt[ch[i]-'a']=new Trie();
			++(p->cnt);
		}
		p=p->nxt[ch[i]-'a'];
	}
	return ;
}

void Del(Trie *rt)
{
	for(int i=0; i<N; i++) if(rt->nxt[i]!=NULL)	Del(rt->nxt[i]);
	free(rt);
	return ;
}

void Dfs(Trie *rt)
{
	Trie *p=rt;
	if(p==NULL)	return ;
	if(p->cnt==0)
	{
		p->win=0;
		p->fail=1;
		return ;
	}

	p->win=p->fail=0;
	for(int i=0; i<N; i++) if(p->nxt[i]!=NULL)
	{
		Dfs(p->nxt[i]);
		if(!p->nxt[i]->win)	p->win=1;
		if(!p->nxt[i]->fail) p->fail=1;
	}
	return ;
}

int main()
{
	while(scanf("%d%d", &n, &k)!=EOF)
	{	
		Trie *rt=new Trie();
		for(int i=1; i<=n; i++)
		{
			scanf("%s", s);
			Insert(rt, s);
		}

		Dfs(rt);
		bool win=rt->win, fail=rt->fail;

		if(win && fail)	printf("First\n");
		else if(fail) printf("Second\n");
		else if(win)
		{
			if(k&1)	printf("First\n");
			else printf("Second\n");
		}
		else if((!win) && (!fail))	printf("Second\n");

		Del(rt);
	}
	return 0;
}
