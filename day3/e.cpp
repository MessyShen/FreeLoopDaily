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
        if(tx<1 || tx>n || ty<1 || ty>n || mmp[tx][ty]) continue;//Խ��
        if(row==1)//������P1��P2����
        {
            if(fx==x)//����һ����ͬһ��
            {
                if(tx!=p1 && tx!=p2)   continue;//�߳�������
                if(x==tx)   continue;//��Ȼ��ͬһ��ûת��
            }
            else//����һ�����Ź�����
            {
                
            }
        }
        else//������P1��P2����
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


