#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std;
const int MAXN = 100000+10;

int rmq[2*MAXN];//rmq���飬����ŷ�����ж�Ӧ���������
struct ST {
    int mm[2*MAXN];
    int dp[2*MAXN][20];//��Сֵ��Ӧ���±�
    void init(int n)
    {
        mm[0] = -1;
        for(int i = 1;i <= n;i++)
        {
            mm[i] = ((i&(i-1)) == 0)?mm[i-1]+1:mm[i-1];
            dp[i][0] = i;
        }
        for(int j = 1; j <= mm[n];j++)
            for(int i = 1; i + (1<<j) - 1 <= n; i++)
                dp[i][j] = rmq[dp[i][j-1]] < rmq[dp[i+(1<<(j-1))][j-1]]?dp[i][j-1]:dp[i+(1<<(j-1))][j-1];
        
    }
    int query(int a,int b)//��ѯ[a,b]֮����Сֵ���±�
    {
        if(a > b)swap(a,b);
        int k = mm[b-a+1];
        return rmq[dp[a][k]] <= rmq[dp[b-(1<<k)+1][k]]?dp[a][k]:dp[b-(1<<k)+1][k];
    }
    
};

//�ߵĽṹ�嶨��
struct Edge{
    int to,next;
};

Edge edge[MAXN*2];
int tot,head[MAXN];
int F[MAXN*2];//ŷ�����У�����dfs������˳�򣬳���Ϊ2*n-1,�±��1��ʼ
int P[MAXN];//P[i]��ʾ��i��F�е�һ�γ��ֵ�λ��

int cnt;
ST st;

void init(){
    tot = 0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v)//�ӱߣ��������Ҫ������
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int u,int pre,int dep)
{
    F[++cnt] = u;
    rmq[cnt] = dep;
    P[u] = cnt;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == pre)continue;
        dfs(v,u,dep+1);
        F[++cnt] = u;
        rmq[cnt] = dep;
    }
}

void LCA_init(int root,int node_num)//��ѯLCAǰ�ĳ�ʼ��
{
    cnt = 0;
    dfs(root,root,0);
    st.init(2*node_num-1);
}

int query_lca(int u,int v)//��ѯu,v��lca���
{
    return F[st.query(P[u],P[v])];
}

bool flag[MAXN];
int main()
{
    int T;
    int N;
    int u,v;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        init();
        memset(flag,false,sizeof(flag));
        for(int i = 1; i < N;i++)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
            flag[v] = true;
        }
        int root;
        for(int i = 1; i <= N; i++)
            if(!flag[i])
            {
                root = i;
                break;
            }
        LCA_init(root,N);
        scanf("%d%d",&u,&v);
        printf("%d\n",query_lca(u,v));
    }
    return 0;
}

