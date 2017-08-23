/**************************************************

【平衡二叉树Avl】
左右子树的高度差最多为一，以此为标准进行旋转。
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
#include<algorithm>
using namespace std;
const int maxn=1000000+10;

int rt, cnt;
struct node
{
	int ch[2], val, idx, h;
	node(int _v=0, int _i=0)
	{
		val=_v, idx=_i, h=1, ch[0]=ch[1]=0;
	}
}tr[maxn];

void Rotate(int &k, int f)
{
	int p=tr[k].ch[f];
	tr[k].ch[f]=tr[p].ch[!f], tr[p].ch[!f]=k;//把孩子的某子树给父亲，更新父亲节点编号
	tr[k].h=max(tr[tr[k].ch[0]].h, tr[tr[k].ch[1]].h)+1;
	tr[p].h=max(tr[tr[p].ch[0]].h, tr[tr[p].ch[1]].h)+1;
	k=p;
	return ;
}

void dbRotate(int &k, int f)
{
	Rotate(tr[k].ch[f], !f);
	Rotate(k, f);
	return ;
}

void Maintain(int &k)
{
	if(tr[tr[k].ch[0]].h==tr[tr[k].ch[1]].h+2)//左儿子更高
	{
		if(tr[tr[k].ch[0]].h==tr[tr[tr[k].ch[0]].ch[0]].h+1)	Rotate(k, 0);//左儿子的左儿子更高，单旋，直接把左儿子提到根节点，则此时根的左右子树高度相同
		else dbRotate(k, 0);//左儿子的右儿子更高，双旋，即第一次单旋把左儿子的右儿子上提成为k的左儿子，此时满足k的左儿子的左儿子更高，再进行第二次单旋
	}
	else if(tr[tr[k].ch[0]].h+2==tr[tr[k].ch[1]].h)
	{
		if(tr[tr[k].ch[1]].h==tr[tr[tr[k].ch[1]].ch[1]].h+1)	Rotate(k, 1);
		else dbRotate(k, 1);
	}
	return ;
}

void Insert(int &k, int val, int idx)
{
	if(!k)	tr[k=++cnt]=node(val, idx);//生成新节点
	else
	{
		Insert(tr[k].ch[val>tr[k].val], val, idx);
		Maintain(k);//维护高度差
	}
	return ;
}

int Delete(int &k, int val)
{
	int ret=0;
	if(val==tr[k].val || (val<tr[k].val && !tr[k].ch[0]) || (val>tr[k].val && !tr[k].ch[1]))
	{
		//删除val
		//val比所有值都小，删除第一个比它大的
		//val比所有值都大，删除第一个比它小的
		if(!tr[k].ch[0] || !tr[k].ch[1])
		{
			ret=tr[k].val;
			k=tr[k].ch[0]+tr[k].ch[1];//若k本就为叶子结点，则k变为0
			return ret;
		}
		ret=tr[k].val=Delete(tr[k].ch[0], val);//删除第一个比val小的数，并将tr[k].val赋为该值
	}	
	else ret=Delete(tr[k].ch[val>tr[k].val], val);
	Maintain(k);
	return ret;
}

int Query(int k, int f)
{
	while(tr[k].ch[f])	k=tr[k].ch[f];////查询最值只可能在最左边节点或最右边节点
	return k;
}

int main()
{	
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
