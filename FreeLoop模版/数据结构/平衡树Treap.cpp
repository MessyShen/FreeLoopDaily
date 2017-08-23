/**************************************************

【平衡二叉树Treap】
如果向二叉排序树里随机插入节点，得到的二叉排序树大多数情况下是平衡的，所以我们增加一个随机值作为二叉树的旋转标准。
***************************************************
POJ3481 Double Queue
Problem
0：系统停止工作
1 k p：客户k以优先级p加入队列
2：队列为空时输出0，否则输出优先级最高的客户并出队
3：队列为空时输出0，否则输出优先级最低的客户并出队
Input
2
1 20 14
1 30 3
2
1 10 99
3
2
2
0
Output
0
20
30
10
0

**************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<algorithm>
using namespace std;
const int maxn=1000000+10;

int rt, cnt;
struct node//Treap：对于每个节点分配一个随机值，将随机值作为优先级进行树的调整
{
	int ch[2], val, idx, rval;//ch左右儿子节点，val节点价值，idx节点编号，rval随机值
	node(int _v=0, int _i=0, int _r=0)
	{
		val=_v, idx=_i, rval=_r, ch[0]=ch[1]=0;
	}
}tr[maxn];

void Rotate(int &k, int f)
{
	int p=tr[k].ch[f];
	tr[k].ch[f]=tr[p].ch[!f], tr[p].ch[!f]=k, k=p;//把孩子的某子树给父亲，更新父亲节点编号
	return ;
}

void Insert(int &k, int val, int idx)
{
	if(!k)	tr[k=++cnt]=node(val, idx, rand());//生成新节点
	else
	{
		int f=(val>tr[k].val);
		Insert(tr[k].ch[f], val, idx);
		if(tr[k].rval<tr[tr[k].ch[f]].rval)	Rotate(k, f);//若子节点优先级更高，旋转
	}
	return ;
}

void Delete(int &k, int val)//删除指定val的节点
{
	if(tr[k].val==val)
	{
		if(tr[k].ch[0] && tr[k].ch[1])
		{
			int f=tr[tr[k].ch[1]].rval>tr[tr[k].ch[0]].rval;
			Rotate(k, f);//上提优先级更高的孩子节点
			Delete(tr[k].ch[f], val);
		}
		else k=tr[k].ch[!tr[k].ch[0]]; 
	}
	else Delete(tr[k].ch[val > tr[k].val], val);
	return ;
}

int Query(int k, int f)
{
	while(tr[k].ch[f])	k=tr[k].ch[f];//查询最值只可能在最左边节点或最右边节点
	return k;
}

int main()
{
	srand(0);//随机种子，time(NULL)可能导致RE，别问我为什么。。。
	
	int d, k, val, idx;
	while(scanf("%d", &d)!=EOF && d)
	{
		if(d==1)
		{
			scanf("%d%d", &idx, &val);
			Insert(rt, val, idx);
		}
		else
		{
			k=Query(rt, d==2);
			printf("%d\n", k ? tr[k].idx : 0);
			if(k)	Delete(rt, tr[k].val);
		}
	}
	return 0;
}
