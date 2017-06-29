/**************************************************
 
 File : b.cpp
 Author : thea
 E-mail : thea-r@outlook.com
 Created : 2017-06-28 08:14:17
 LastModify : 2017-06-28 09:24:18
 
 **************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<stack>
#include<cmath>
#include<algorithm>
using namespace std;
const int NN=500+10;
const int maxn=NN*32*2+10;
const int maxm=maxn*10+10;

int n, N, b[NN][NN], tp[32];
int cur, fir[maxn], nxt[maxm], ver[maxm];
int idx, tot, w[maxn], low[maxn], dfn[maxn];
bool ins[maxn];
stack<int> stk;
struct node
{
    int u, v;
}a[maxn][32];

void Read()
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            scanf("%d", &b[i][j]);
    return ;
}

void Add(int u, int v)
{
    ver[++cur]=v, nxt[cur]=fir[u], fir[u]=cur;
    return ;
}

void Init()
{
    N=0;
    for(int i=1; i<=n; i++)
        for(int j=0; j<=31; j++)
        {
            a[i][j].u=++N;
            a[i][j].v=++N;
        }
    
    cur=0;
    memset(fir, 0, sizeof fir);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {
            if(i==j)	continue;
            else
            {
                for(int k=0, num=b[i][j]; k<=31; k++)
                {
                    tp[k]=num&1;
                    num>>=1;
                }
                if(i%2==1 && j%2==1)
                {
                    for(int k=0; k<=31; k++)	// |
                    {
                        if(tp[k]==0)
                        {
                            Add(a[i][k].u, a[j][k].u);//0 0
                            
                            Add(a[j][k].u, a[i][k].u);//0 0
                        }
                        else if(tp[k]==1)
                        {
                            Add(a[i][k].u, a[j][k].v);//0 1
                            Add(a[i][k].v, a[j][k].u);//1 0
                            Add(a[i][k].v, a[j][k].v);//1 1
                            
                            Add(a[j][k].u, a[i][k].v);//1 0
                            Add(a[j][k].v, a[i][k].u);//0 1
                            Add(a[j][k].v, a[i][k].v);//1 1
                        }
                    }
                }
                else if(i%2==0 && j%2==0)	// &
                {
                    for(int k=0; k<=31; k++)
                    {
                        if(tp[k]==0)
                        {
                            Add(a[i][k].u, a[j][k].u);//0 0
                            Add(a[i][k].u, a[j][k].v);//0 1
                            Add(a[i][k].v, a[j][k].u);//1 0
                            
                            Add(a[j][k].u, a[i][k].u);//0 0
                            Add(a[j][k].u, a[i][k].v);//1 0
                            Add(a[j][k].v, a[i][k].u);//0 1
                        }
                        else if(tp[k]==1)
                        {
                            Add(a[i][k].v, a[j][k].v);//1 1
                            
                            Add(a[j][k].v, a[i][k].v);//1 1
                        }
                    }
                }
                else	// ^
                {
                    for(int k=0; k<=31; k++)
                    {
                        if(tp[k]==0)
                        {
                            Add(a[i][k].u, a[j][k].u);//0 0
                            Add(a[i][k].v, a[j][k].v);//1 1
                            
                            Add(a[j][k].u, a[i][k].u);//0 0
                            Add(a[j][k].v, a[i][k].v);//1 1
                        }
                        else
                        {
                            Add(a[i][k].u, a[j][k].v);//0 1
                            Add(a[i][k].v, a[j][k].u);//1 0
                            
                            Add(a[j][k].u, a[i][k].v);//1 0
                            Add(a[j][k].v, a[i][k].u);//0 1
                        }
                    }
                }
            }
        }
    return ;
}

void Tarjan(int u)
{
    dfn[u]=low[u]=++idx;
    ins[u]=true;
    stk.push(u);
    
    for(int i=fir[u], v; i; i=nxt[i])
    {
        if(!dfn[v=ver[i]])
        {
            Tarjan(v);
            low[u]=min(low[u], low[v]);
        }
        else if(ins[v])	low[u]=min(low[u], low[v]);
    }
    
    if(dfn[u]==low[u])
    {
        int v=stk.top();
        stk.pop();
        
        w[v]=++tot, ins[v]=false;
        while(v!=u)
        {
            v=stk.top();
            stk.pop();
            w[v]=tot, ins[v]=false;
        }
    }
    return ;
}

bool ok()
{
    for(int i=1; i<=n; i++)
        for(int j=0; j<=31; j++)
            if(w[a[i][j].u]==w[a[i][j].v])
                return false;
    return true;
}

bool Work()
{
    tot=idx=0;
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(ins, 0, sizeof ins);
    while(!stk.empty())	stk.pop();
    for(int i=1; i<=N; i++)
    {
        if(b[i][i])	return false;
        if(!dfn[i])	Tarjan(i);
    }
    return ok();
}

int main()
{
    while(scanf("%d", &n)!=EOF)
    {
        Read();
        Init();
        Work() ? printf("YES\n") : printf("NO\n");
    }
    return 0;
}
