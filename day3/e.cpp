#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<ctype.h>
#include<math.h>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<bitset>
#include<algorithm>
#include<time.h>
using namespace std;
const int maxn=512+10;

int T, n, tot, dd[4][2]={-1, 0, 0, 1, 1, 0, 0, -1};
int mmp[maxn][maxn];

void Dfs1(int x, int y, int fx, int fy, int in, int row, int p1, int p2)
{
    mmp[x][y]=++tot;
    
    for(int i=0, tx, ty; i<4; i++)
    {
        tx=x+dd[i][0], ty=y+dd[i][1];
        if(tx<1 || tx>n || ty<1 || ty>n || mmp[tx][ty]) continue;//越界
        if(row==1)//横着走P1、P2两行
        {
            if(fx==x)//和上一格在同一行
            {
                if(tx!=p1 && tx!=p2)   continue;//走出这两行
                if(x==tx)   continue;//仍然在同一行没转弯
            }
            else//从上一格竖着过来的
            {
                
            }
        }
        else//竖着走P1、P2两列
        {
            if(fx==x)
            {
                if(ty!=p1 && ty!=p2)    continue;
                if(x==tx)   continue;
            }
            else
            {
                
            }
        }
    }
    return ;
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        tot=0;
        memset(mmp, 0, sizeof mmp);
        
        scanf("%d", &n);
        if(n&1)
        {
            tot=0;
            Dfs1(2, 1, 2, 0, 1, 1, 1, 2);
        }
        else
        {
            
        }
    }
    return 0;
}


