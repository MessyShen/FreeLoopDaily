/**************************************************

【平衡二叉树SBT】
每棵子树的大小不小于其兄弟的子树大小，以此为标准进行旋转。
SBT支持查询val的排名和rank[i]的值，支持查询节点的前驱和后继。
***************************************************
BZOJ 1208 [HNOI2004]宠物收养所]
Problem
n组操作，对于每一对(x, y)：
x=0时，收养一个特点值为y的宠物，若此时有人未领养，选择最接近的人。
x=1时，来一个希望领养特点值为y的宠物的人，若此时有宠物，选择最接近的宠物。
对于每一次领养，记录abs(希望值-特点值)，求和输出。
Input
5
0 2
0 4
1 3
1 2
1 5
Output
3

**************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=80000+10, mod=1000000;

int n, rt, cnt, ans;
struct node
{
	int ch[2], val, siz;
	node(int _v=0)
	{
		val=_v, siz=1, ch[0]=ch[1]=0;
	}
}tr[maxn];

void Rotate(int &k, int f)
{
	int p=tr[k].ch[f];
	tr[k].ch[f]=tr[p].ch[!f], tr[p].ch[!f]=k;//把孩子的某子树给父亲，更新父亲节点编号
	tr[k].siz=tr[tr[k].ch[0]].siz+tr[tr[k].ch[1]].siz+1;
	tr[p].siz=tr[tr[p].ch[0]].siz+tr[tr[p].ch[1]].siz+1;
	k=p;
	return ;
}

void dbRotate(int &k, int f)
{
	Rotate(tr[k].ch[f], !f);
	Rotate(k, f);
	return ;
}

void Maintain(int &k, int f)
{
	if(k && tr[tr[tr[k].ch[f]].ch[f]].siz>tr[tr[k].ch[!f]].siz)
	{
		Rotate(k, f);
		Maintain(tr[k].ch[0], 0), Maintain(tr[k].ch[1], 1);//旋转之后一定要对子树进行维护
		Maintain(k, 0), Maintain(k, 1);
	}
	else if(k && tr[tr[tr[k].ch[f]].ch[!f]].siz>tr[tr[k].ch[!f]].siz)
	{
		dbRotate(k, f);
		Maintain(tr[k].ch[0], 0), Maintain(tr[k].ch[1], 1);
		Maintain(k, 0), Maintain(k, 1);
	}
	return ;
}

void Insert(int &k, int val)
{
	if(!k)	tr[k=++cnt]=node(val);//生成新节点
	else
	{
		++tr[k].siz;
		Insert(tr[k].ch[val>tr[k].val], val);
		Maintain(k, val>tr[k].val);//维护size
	}
	return ;
}

int Delete(int &k, int val)
{
	--tr[k].siz;
	if(val==tr[k].val || (val<tr[k].val && !tr[k].ch[0]) || (val>tr[k].val && !tr[k].ch[1]))
	{
		//删除val
		//val比所有值都小，删除第一个比它大的
		//val比所有值都大，删除第一个比它小的
		if(!tr[k].ch[0] || !tr[k].ch[1])
		{
			int ret=tr[k].val;
			k=tr[k].ch[0]+tr[k].ch[1];//若k本就为叶子结点，则k变为0
			return ret;
		}
		return  tr[k].val=Delete(tr[k].ch[0], val);//删除第一个比val小的数，并将tr[k].val赋为该值
	}
	return Delete(tr[k].ch[val>tr[k].val], val);
}

bool Find(int k, int val)//查询val是否在树中
{
	if(!k)	return false;
	if(tr[k].val==val)	return true;
	return Find(tr[k].ch[val>tr[k].val], val);
}

int Find_pre(int k, int val)
{
	if(!k)	return val;
	if(val<=tr[k].val)	return Find_pre(tr[k].ch[0], val);
	int tmp=Find_pre(tr[k].ch[1], val);
	return tmp==val ? tr[k].val : tmp;//如果tmp和val相等，说明右子树所有节点都比val大，当前节点就是前驱
}

int Find_sub(int k, int val)
{
	if(!k)	return val;
	if(val>=tr[k].val)	return Find_sub(tr[k].ch[1], val);
	int tmp=Find_sub(tr[k].ch[0], val);
	return tmp==val ? tr[k].val : tmp;//如果tmp和val相等，说明左子树所有节点都比val小，当前节点就是后继
}

int Query(int k, int f)
{
	while(tr[k].ch[f])	k=tr[k].ch[f];//查询最值只可能在最左边节点或最右边节点
	return k;
}

int main()
{	
	while(scanf("%d", &n)!=EOF)
	{
		rt=0, ans=0, cnt=0;
		for(int i=1, a, b, type=0, sum=0; i<=n; i++)
		{
			scanf("%d%d", &a, &b);
			if(sum==0 || a==type)
			{
				Insert(rt, b);
				++sum;
				type=a;
			}
			else if(Find(rt, b))
			{
				Delete(rt, b);
				--sum;
			}
			else
			{
				int pre=Find_pre(rt, b), sub=Find_sub(rt, b), tmp;
				if(pre==b || sub==b)	tmp=pre+sub-b;//如果没有前驱或没有后继
				else tmp=(b-pre<=sub-b ? pre : sub);
				Delete(rt, tmp);
				--sum;
				ans=(ans+abs(b-tmp))%mod;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
