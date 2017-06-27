/**************************************************

      File : a.cpp
      Author : thea
      E-mail : thea-r@outlook.com
      Created : 2017-06-27 10:21:51
      LastModify : 2017-06-27 10:23:37

**************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;
const int maxn=100000+10;
typedef long long lint;
const lint INF=1e18;

int T, n, m;
struct node
{
    lint s, p, w;
    bool operator <(const node&t)const
    {
        return w>t.w;
    }
    node(lint _s=0, lint _p=0)
    {
        s=_s, p=_p, w=_s*_p;
    }
}a[maxn];
struct node2
{
    int id;
    lint q, ans;
}b[maxn];

bool cmp1(node2 t1, node2 t2)
{
    return t1.q<t2.q;
}

bool cmp2(node2 t1, node2 t2)
{
    return t1.id<t2.id;
}

void Work()
{
    sort(b+1, b+1+m, cmp1);
    
    priority_queue<node> que;
    
    for(int i=m, cur=n; i>=1; i--)
    {
        while(cur && a[cur].s>b[i].q)
        {
            que.push(a[cur]);
            cur--;
        }
        
        lint ans=INF;
        if(!que.empty())    ans=min(ans, que.top().w);
		else ans=min(ans, a[n].p*b[i].q);
        if(cur && a[cur].s<=b[i].q)    ans=min(ans, a[cur].p*b[i].q);
        b[i].ans=ans;
    }
    
    sort(b+1, b+1+m, cmp2);
    for(int i=1; i<=m; i++)    printf("%lld\n", b[i].ans);
    return ;
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; i++)
        {
            scanf("%lld%lld", &a[i].s, &a[i].p);
            a[i].w=a[i].s*a[i].p;
        }
        for(int i=1; i<=m; i++)
        {
            scanf("%lld", &b[i].q);
            b[i].id=i;
        }
        
        Work();
    }
    return 0;
}
