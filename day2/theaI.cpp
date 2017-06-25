#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=400000+10;

int n, m, tot, rmq[maxn], P[maxn], F[maxn];
int cur, fir[maxn], nxt[maxn], ver[maxn];
int xk, yk, x[maxn], y[maxn];
bool vis[maxn];
struct ST
{
    int mm[maxn], dp[maxn][20];
    void init(int n)
    {
        mm[0]=-1;
        for(int i=1; i<=n; i++)
        {
            mm[i]=((i&(i-1))==0) ? mm[i-1]+1 : mm[i-1];
            dp[i][0]=i;
        }
        
        for(int j=1; j<=mm[n]; j++)
            for(int i=1; i+(1<<j)-1<=n; i++)
                dp[i][j]=rmq[dp[i][j-1]] < rmq[dp[i+(1<<(j-1))][j-1]] ? dp[i][j-1] : dp[i+(1<<(j-1))][j-1];
    }
    int query(int a, int b)
    {
        if(a>b) swap(a, b);
        int k=mm[b-a+1];
        return rmq[dp[a][k]] <= rmq[dp[b-(1<<k)+1][k]] ? dp[a][k] : dp[b-(1<<k)+1][k];
    }
}st;

void Add(int u, int v)
{
    ver[++cur]=v, nxt[cur]=fir[u], fir[u]=cur;
    ver[++cur]=u, nxt[cur]=fir[v], fir[v]=cur;
    return ;
}

int query(int u, int v)
{
    return rmq[st.query(P[u], P[v])];
}

bool cmp(int a, int b)
{
    return P[a]<P[b];
}

int Work()
{
    int ans=0, cnt, u;
    
    sort(y, y+yk, cmp);
    
    for(int i=0; i<xk; i++)
    {
        u=x[i];
        cnt=lower_bound(y, y+yk, u, cmp)-y;
        
        if(cnt<yk) ans=max(ans, query(x[i], y[cnt]));
        else ans=max(ans, query(x[i], y[cnt-1]));
        
        if(cnt>0)   ans=max(ans, query(x[i], y[cnt-1]));
    }
    return ans;
}

void Dfs(int u, int d)
{
    vis[u]=true;
    F[++tot]=u;
    rmq[tot]=d;
    P[u]=tot;
    
    for(int i=fir[u], v; i ; i=nxt[i])
        if(!vis[v=ver[i]])
        {
            Dfs(v, d+1);
            F[++tot]=u;
            rmq[tot]=d;
        }
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
        
        memset(vis, 0, sizeof vis);
        memset(P, 0, sizeof P);
        memset(F, 0, sizeof F);
        memset(rmq, 0, sizeof rmq);
        tot=0;
        Dfs(1, 0);
        st.init(2*n-1);
        
        
        for(int i=1; i<=m; i++)
        {
            scanf("%d", &xk);
            for(int j=0; j<xk; j++)	scanf("%d", &x[j]);
            scanf("%d", &yk);
            for(int j=0; j<yk; j++)	scanf("%d", &y[j]);
            
            printf("%d\n", Work()+1);
        }
    }
    return 0;
}
