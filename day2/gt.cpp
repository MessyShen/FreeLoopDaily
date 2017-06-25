#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long lint;
const int maxn=3000+10;

int n;

int p[100100];

int main()
{
	int t;
	cin>>t;
	while(t --)
	{
		cin>:>n;
		for(int i = 2;i <= n;i ++)
			cin>>p[i];
		if(n % 2)
		{
			cout<<"No"<<endl;
			continue;
		}
		bool f = true;
		int sum = 0;
		for(int i = n;i >= 2;i --)
		{
			if(p[i] == 1)
			{
				sum ++;
			}
			else
			{
				if(sum == 0)
				{
					f = false;
					break;
				}
				sum --;
			}
		}
		if(f)
			cout<<"Yes"<<endl;
		else 
			cout<<"No"<<endl;
	}
	return 0;
}

