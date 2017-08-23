# Free Loop 模板 To-do-list

[TOC]

## 数据结构

##### 字符串哈希

```C++
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
```

##### 堆

```c++
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
```

##### 左偏树

##### 平衡二叉树Treap

```c++
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
```

##### 平衡二叉树Avl
```c++
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
```

##### 平衡二叉树SBT

```C++
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
```

##### 伸展树

##### 并查集
##### 集合计数问题
##### 二分图的识别
##### 二叉排序树
##### 线段树
##### 一维线段树
##### 二维线段树
##### 树状数组
##### 一维树状数组
##### N维树状数组
##### 字典树
##### 后缀数组，后缀树
##### 块状链表
##### 哈夫曼树
##### 桶，跳跃表
##### Trie树(静态建树、动态建树)
##### AC自动机

##### Fail树

```c++
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
```

##### LCA和RMQ问题
##### KMP算法
##### 后缀自动机
##### 回文自动机

## 图论

##### 基本图算法图
##### 广度优先遍历
##### 深度优先遍历
##### 拓扑排序
##### 割边割点
##### 强连通分量
##### Tarjan算法
##### 双连通分量
##### 强连通分支及其缩点
##### 图的割边和割点
##### 最小割模型、网络流规约
##### 2-SAT问题
##### 欧拉回路
##### 哈密顿回路
##### 最小生成树
##### Prim算法
##### Kruskal算法(稀疏图)
##### Sollin算法
##### 次小生成树
##### 第k小生成树
##### 最优比例生成树
##### 最小树形图
##### 最小度限制生成树
##### 平面点的欧几里德最小生成树
##### 平面点的曼哈顿最小生成树
##### 最小平衡生成树
##### 最短路径
##### 有向无环图的最短路径->拓扑排序
##### 非负权值加权图的最短路径->Dijkstra算法(可使用二叉堆优化)
##### 含负权值加权图的最短路径->Bellmanford算法
##### 含负权值加权图的最短路径->Spfa算法
##### (稠密带负权图中SPFA的效率并不如Bellman-Ford高)
##### 全源最短路弗洛伊德算法Floyd
##### 全源最短路Johnson算法
##### 次短路径
##### 第k短路径
##### 差分约束系统
##### 平面点对的最短路径(优化)
##### 双标准限制最短路径
##### 最大流
##### 增广路->Ford-Fulkerson算法
##### 预推流
##### Dinic算法
##### 有上下界限制的最大流
##### 节点有限制的网络流
##### 无向图最小割->Stoer-Wagner算法
##### 有向图和无向图的边不交路径
##### Ford-Fulkerson迭加算法
##### 含负费用的最小费用最大流
##### 匹配
##### Hungary算法
##### 最小点覆盖
##### 最小路径覆盖
##### 最大独立集问题
##### 二分图最优完备匹配Kuhn-Munkras算法
##### 不带权二分匹配：匈牙利算法
##### 带权二分匹配：KM算法
##### 一般图的最大基数匹配
##### 一般图的赋权匹配问题
##### 拓扑排序
##### 弦图
##### 稳定婚姻问题

## 搜索

##### 广搜的状态优化
##### 利用M进制数存储状态
##### 转化为串用hash表判重
##### 按位压缩存储状态
##### 双向广搜
##### A*算法
##### 深搜的优化
##### 位运算
##### 剪枝
##### 函数参数尽可能少
##### 层数不易过大
##### 双向搜索或者是轮换搜索
##### IDA*算法
##### 记忆化搜索

## 动态规划

##### 四边形不等式理论
##### 不完全状态记录
##### 青蛙过河问题
##### 利用区间dp
##### 背包类问题
##### 0-1背包，经典问题
##### 无限背包，经典问题
##### 判定性背包问题
##### 带附属关系的背包问题
##### 双背包求最优值
##### 构造三角形问题
##### 带上下界限制的背包问题(012背包)
##### 线性的动态规划问题
##### 积木游戏问题
##### 决斗（判定性问题）
##### 圆的最大多边形问题
##### 统计单词个数问题
##### 棋盘分割
##### 日程安排问题
##### 最小逼近问题(求出两数之比最接近某数/两数之和等于某数等等)
##### 方块消除游戏(某区间可以连续消去求最大效益)
##### 资源分配问题
##### 数字三角形问题
##### 漂亮的打印
##### 邮局问题与构造答案
##### 最高积木问题
##### 两段连续和最大
##### 2次幂和问题
##### N个数的最大M段子段和
##### 交叉最大数问题
##### 判定性问题的dp(如判定整除、判定可达性等)
##### 模K问题的dp
##### 特殊的模K问题，求最大(最小)模K的数
##### 变换数问题
##### 单调性优化的动态规划
##### 1-SUM问题
##### 2-SUM问题
##### 序列划分问题(单调队列优化)
##### 剖分问题(多边形剖分/石子合并/圆的剖分/乘积最大)
##### 凸多边形的三角剖分问题
##### 乘积最大问题
##### 多边形游戏(多边形边上是操作符,顶点有权值)
##### 石子合并(N^3/N^2/NLogN各种优化)
##### 贪心的动态规划
##### 最优装载问题
##### 部分背包问题
##### 乘船问题
##### 贪心策略
##### 双机调度问题Johnson算法
##### 状态dp
##### 牛仔射击问题(博弈类)
##### 哈密顿路径的状态dp
##### 两支点天平平衡问题
##### 一个有向图的最接近二部图
##### 树型dp
##### 完美服务器问题(每个节点有3种状态)
##### 小胖守皇宫问题
##### 网络收费问题
##### 树中漫游问题
##### 树上的博弈
##### 树的最大独立集问题
##### 树的最大平衡值问题
##### 构造树的最小环

## 数论

##### 中国剩余定理
##### 欧拉函数
##### 欧几里得定理
##### 欧几里德辗转相除法求GCD(最大公约数)
##### 扩展欧几里得
##### 大数分解与素数判定
##### 佩尔方程
##### 同余定理(大数求余)
##### 素数测试
##### 一千万以内：筛选法
##### 一千万以外：米勒测试法
##### 连分数逼近
##### 因式分解
##### 循环群生成元
##### 素数与整除问题
##### 进制位.
##### 同余模运算
##### 组合数学
##### 排列组合
##### 容斥原理
##### 递推关系和生成函数
##### Polya计数法
##### Polya计数公式
##### Burnside定理
##### N皇后构造解
##### 幻方的构造
##### 满足一定条件的hamilton圈的构造
##### Catalan数
##### Stirling数
##### 斐波拉契数
##### 调和数
##### 连分数
##### MoB8ius反演
##### 偏序关系理论
##### 加法原理和乘法原理

## 计算几何

##### 基本公式
##### 叉乘
##### 点乘
##### 常见形状的面积、周长、体积公式
##### 坐标离散化
##### 线段
##### 判断两线段（一直线、一线段）是否相交
##### 求两线段的交点
##### 多边形
##### 判定凸多边形,顶点按顺时针或逆时针给出,(不)允许相邻边共线
##### 判点在凸多边形内或多边形边上,顶点按顺时针或逆时针给出
##### 判点在凸多边形内,顶点按顺时针或逆时针给出,在多边形边上返回0
##### 判点在任意多边形内,顶点按顺时针或逆时针给出
##### 判线段在任意多边形内,顶点按顺时针或逆时针给出,与边界相交返回1
##### 多边形重心
##### 多边形切割(半平面交)
##### 扫描线算法
##### 多边形的内核
##### 三角形
##### 内心
##### 外心
##### 重心
##### 垂心
##### 费马点
##### 圆
##### 判直线和圆相交,包括相切
##### 判线段和圆相交,包括端点和相切
##### 判圆和圆相交,包括相切
##### 计算圆上到点p最近点,如p与圆心重合,返回p本身
##### 计算直线与圆的交点,保证直线与圆有交点
##### 计算线段与圆的交点可用这个函数后判点是否在线段上
##### 计算圆与圆的交点,保证圆与圆有交点,圆心不重合
##### 计算两圆的内外公切线
##### 计算线段到圆的切点
##### 点集最小圆覆盖
##### 可视图的建立
##### 对踵点
##### 经典问题
##### 平面凸包
##### 三维凸包
##### Delaunay剖分/Voronoi图

## 计算方法

##### 二分法
##### 二分法求解单调函数相关知识
##### 用矩阵加速的计算
##### 迭代法
##### 三分法
##### 解线性方程组
##### LUP分解
##### 高斯消元
##### 解模线性方程组
##### 定积分计算
##### 多项式求根
##### 周期性方程
##### 线性规划
##### 快速傅立叶变换
##### 随机算法
##### 0/1分数规划
##### 三分法求解单峰(单谷)的极值
##### 迭代逼近
##### 矩阵法

## 博弈论

##### 极大极小过程
##### Nim问题

## STL

##### 优先队列
##### 双端队列

##### set

##### map

##### iterator

##### unique

##### upper_bound、lower_bound

##### sprintf

##### next_permutation

## ？？？

##### 可并堆
##### 左偏堆

##### 栈，队列，链表