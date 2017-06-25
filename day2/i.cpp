 #include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std;
const int maxn=100000+10;

int n, m, tot, rmq[maxn], cnt[maxn], pre[maxn], f[maxn];
int cur, fir[maxn], nxt[maxn<<1], ver[maxn<<1];
bool vis[maxn];
map<pair<int, int>, int> mmp;
struct ST
{
    int nm[2*maxn], dp[2*maxn];
    void init(int n)
    {
        mm[0]=-1;
        for(int i=1; i<=n; i++)
        {
            mm[i]=((i&(i-1))==0) ? mm[i-1]+1: mm[i-1];
            dp[i][0]=i;
        }
        for(int j=1; j<=mm[n]; j++)
            for(int i=1; i+(1<<j)-1<=n; i++)
                dp[i][j]=rmq[dp[i][j-1]]<rmq[dp[i+(1<<(j-1))][j-1]]?dp[i][j-1]:dp[i+(1<<(j-1))][j-1];
    }
    int query(int a, int b)
    {
        if(a>b) swap(a, b);
        int k=mm[b-a+1];
        return rmq[dp[a][k]]<=rmq[dp[b-(1<<k)+1][k]]?dp[a][k]:dp[b-(1<<k)+1][k];
    }
}st;
struct point
{
    int id, w;
    bool operator <(const point&t)const
    {
        return w<t.w;
    }
    void sc()
    {
        scanf("%d", &id);
        w=cnt[id];
        return ;
    }
};
struct node
{
    int k;
    point p[maxn];
    void sc()
    {
        scanf("%d", &k);
        for(int i=0; i<k; i++)	p[i].sc();
        sort(p, p+k);
        return ;
    }
    void pr()
    {
        for(int i=0; i<k; i++) printf("%d%c", p[i].id, " \n"[i==k]);
        return ;
    }
};

void Add(int u, int v)
{
    ver[++cur]=v, nxt[cur]=fir[u], fir[u]=cur;
    ver[++cur]=u, nxt[cur]=fir[v], fir[v]=cur;
    return ;
}

int query(int u, int v)
{
    return st.query(f[u], f[v]);
}

int Work(node x, node y)
{
    int ans=0, cnt;
    for(int i=0; i<x.k; i++)
    {
        point u=x.p[i];
        cnt=lower_bound(y.p, y.p+y.k, u)-y.p;
        ans=max(ans, query(x.p[i].id, y.p[cnt].id));
        if(cnt>0)   ans=max(ans, query(x.p[i].id, y.p[cnt-1].id));
    }
    return ans;
}

void Dfs(int u, int d)
{
    vis[u]=true;
    f[++tot]=u;
    rmq[tot]=d;
    cnt[u]=tot;
    
    for(int i=fir[u], v; i; i=nxt[i])
        if(!vis[v=ver[i]])
            Dfs(v, d+1);
    return ;
}

void ST_init()
{
    
    return ;
}

void Init(int root, int node_num)
{
    memset(vis, 0, sizeof vis);
    memset(cnt, 0, sizeof cnt);
    tot=0;
    Dfs(root, 0);
    ST_init();
    return ;
}

int main()
{
    while(scanf("%d%d", &n, &m)!=EOF)
    {
        cur=0;
        memset(fir, 0, sizeof fir);
        for(int i=1, u, v; i<n; i++)
        {
            scanf("%d%d", &u, &v);
            Add(u, v);
        }
        
        Init(1, n);

        node x, y;
        for(int i=1; i<=m; i++)
        {
            x.sc(), y.sc();
            printf("%d\n", Work(x, y));
        }
    }
    return 0;
}

