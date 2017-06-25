#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
const int maxn=1200+10;

int n,k;
int mod = 1000000007;

int get(int x)
{
	int ans = 1;
	for(int i = 1;i <= k;i ++)
	{
		ans = ans * x % mod;
	}
	return ans;
}
int main()
{
	int t;
	cin>>t;
	while(t --)
	{
		cin>>n>>k;
		int sum = 0;
		for(int i = 1;i <= n;i ++)
		{
			sum += get(i);
			sum %= mod;
		}
		cout<<sum<<endl;
	}
}
