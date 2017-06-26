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
const int MAXN = 1000+10;

char s[10010];

int main() {
	int T;
	scanf("%d", &T);
	int n, op, l; //n:number op:*
	while (T--){
		scanf("%s", s);
		n = 0; op = 0;
		int len = strlen(s);
		l = len-1;
		int ans = 0;
		int totaln = 0, totalop= 0;
		for (int i = 0; i < len; ++i){
			if (s[i] == '*') totalop++;
			else totaln++;
		}
		if (totaln < totalop + 1) {
			ans += totalop + 1 - totaln;
			n = ans;
		}
	//	cout << n << " " << ans << ": " << endl;

		while (s[l] == '*' && l >= 0) l--;
		for (int i = 0; i < len; ++i){
			if (s[i] != '*') {
				n++; continue;
			}
			if (n < 2) {
				if (l > i) {
					swap(s[i], s[l]);
					n+=1;
					ans++;
					while (s[l] == '*' && l >= 0) l--;
					continue;
				} else {
					ans += (2 - n);
					n = 1;
					continue;
				}
			} else n--;
			//printf("%s\n", s);
		}
		if (s[len -1] !='*') ans++;
		printf("%d\n", ans);
	}
	return 0;
}
