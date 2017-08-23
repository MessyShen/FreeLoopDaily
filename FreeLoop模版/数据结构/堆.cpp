/**************************************************

【堆】
堆是一棵完全二叉树，堆中某个节点的值总是不大于或不小于其父节点的值。
将根节点最大的堆是大根堆，根节点最小的堆是小根堆。
普通的堆合并可以逐个插入，合在一起重新建堆，对于更高的合并要求可以选择左偏树。
***************************************************
UESTC 204 合并果子
Problem
合并n堆果子，每次任意合并两堆，消耗的体力为两堆果子重量之和，求总最小消耗。
Input
3
1 2 9
Output
15

**************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define kl (k<<1)
#define kr ((k<<1)+1)
using namespace std;
const int maxn=10000+10;

int n, a[maxn];

void Maintain(int k)//维护以k为根的小根堆，满足a[k]<=a[kl]&&a[k]<=a[kr]
{
	while(kl<=n)
	{
		if(kr<=n && a[kl]>a[kr] && a[k]>a[kr])  swap(a[k], a[kr]), k=kr;
		else if(a[k]>a[kl]) swap(a[k], a[kl]), k=kl;
		else break;
	}
	return ;
}

void Build()
{
	for(int i=n>>1; i; i--) Maintain(i);//叶子节点不用考虑，所以i从n/2开始调整
	return ;
}

void Delete()
{
	swap(a[1], a[n--]);//删除操作只会出现在堆顶
	Maintain(1);
	return ;
}

void Add(int val)//新元素加入到堆底 向下调整
{
	a[++n]=val;
	for(int k=n; k>1 && a[k]<a[k>>1]; k>>=1)  swap(a[k], a[k>>1]);
	return ;
}

int main()
{
	while(scanf("%d", &n)!=EOF)
	{
		for(int i=1; i<=n; i++) scanf("%d", &a[i]);
		Build();

		int ans=0, tmp;
		while(n-1)
		{
			tmp=a[1], Delete();
			tmp+=a[1], Delete();
			ans+=tmp, Add(tmp);
		}
		printf("%d\n", ans);
	}
	return 0;
}
