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

double pi = acos(-1.0);
double eps = 1e-9;

int R,r,H,F,S;

double ans;

bool isok(double a,double b)
{
    if(fabs(a - b) <= eps)
        return true;
    return false;
}

double getarea(double r,double h)
{
    int re = 3,le = 1e5,mid;
    double res;
    
    //cout<<r<<" "<<h<<endl;
    
    while(re < le)
    {
        mid = (re + le + 1) >> 1;
        double a = tan(pi / mid);
        double s = 2.0 * a * r * h;
        if(s >= S)
        {
            res = s * mid;
            re = mid;
        }
        else
        {
            le = mid - 1;
        }
        //cout<<re <<" "<<le<<endl;
    }
    return res;
}

int main()
{
    while(~scanf("%d%d%d%d%d",&R,&r,&H,&F,&S))
    {
        double ans = 0.0;
        double radd = (R - r) / 1.0 / F;
        double h = H / 1.0 / F;
        for(int i = 0;i < F;i ++)
        {
            ans += getarea(r + i * radd,h);
        }
        printf("%.3f\n",ans);
    }
}
