day3

## 补ZOJ3868 （Mobius）

很玄学的一道题 用了C++0x编译器过了 不然TLE

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>

typedef long long LL;
#define MOD 998244353

using namespace std;

const int maxN = 1e6+10;
int n, k, len;
int pow2[maxN], num[maxN];
int prime[maxN], u[maxN];
bool vis[maxN];

void mobius() {
    memset(vis, false,sizeof(vis));
    u[1] = 1;
    int cnt = 0;
    for(int i = 2; i < maxN; i++) {
        if (!vis[i]) {
            prime[cnt++] = i;
            u[i] = -1;
        }
        for(int j = 0; j < cnt && i*prime[j] < maxN; j++) {
            vis[i*prime[j]] = true;
            if (i % prime[j]) {
                u[i*prime[j]] = -u[i];
            }
            else {
                u[i*prime[j]] = 0;
                break;
            }
        }
    }
}

void init() {
    mobius();
    pow2[0] = 1;
    for (int i = 1; i < maxN; ++i){
        pow2[i] = 2 * pow2[i-1] % MOD;
    }
}

LL quickPow(LL x, int n) {
    LL res = 1;
    while (n != 0) {
        if(n & 1)
            res = (res * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return res;
}


int main() {
    init();
    int T;
    scanf("%d", &T);
    for (int times = 1; times <= T; ++times) {
        int tmp;
        len = 0;
        scanf("%d%d", &n, &k);
        memset(num, 0, sizeof(num));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &tmp);
            len = max(len, tmp);
            num[tmp]++;
        }
        for (int i = 1; i <= len; ++i) {
            for (int j = i*2; j <= len; j += i)
                num[i] += num[j];
        }
        LL ans = 0, val;
        for (int i = 1; i <= len; ++i) {
            val = quickPow(i, k);
            for (int j = i; j <= len; j += i) {
                ans += ((LL)u[j/i] * val % MOD) * (pow2[num[j]]-1) % MOD;
                ans = (ans % MOD + MOD) % MOD;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}

```