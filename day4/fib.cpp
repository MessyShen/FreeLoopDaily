#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <math.h>

#define eps 1e-8
using namespace std;
typedef unsigned long long LL;

//斐波那契循环节模板
/*
 input :
 5
 11
 19
 61
 17
 67890
 output :
 Case #1: 10
 Case #2: 18
 Case #3: 60
 Case #4: 36
 Case #5: 4440
 */

LL n;

LL gcd(LL a, LL b){
    return (b == 0)? a : gcd(b, a % b);
}

LL lcm(LL a,LL b) {
    return a * b / gcd(a,b);
}

void mul(LL A[2][2],LL B[2][2],LL ret[2][2],LL mod) {
    LL C[2][2] = { 0 };
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j] % mod) % mod;
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            ret[i][j] = C[i][j];
        }
    }
}

void qpow(LL base[2][2],LL p,LL dest[2][2],LL mod) {
    LL ret[2][2] = { 0 };
    ret[0][0] = ret[1][1] = 1;
    
    while (p > 0) {
        if (p & 1) mul(ret, base, ret, mod);
        mul(base, base, base, mod);
        p >>= 1;
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            dest[i][j] = ret[i][j];
        }
    }
    
}

LL qpow(LL base,LL p,LL mod) {
    LL ret = 1;
    while (p) {
        if (p & 1) ret = ret * base % mod;
        base = base * base % mod;
        p >>= 1;
    }
    return ret;
}

LL S[10000], c;
LL f1, f2;
void F(LL p,LL mod) {
    LL A[2][2] = { 0 };
    A[0][0] = 1; A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 0;
    qpow(A, p-1, A, mod);
    f1 = (A[1][0]+A[1][1]) % mod;
    f2 = (A[0][0] + A[0][1]) % mod;
}

LL loop(LL mod) {
    if (mod == 2) return 3;
    else if (mod == 3) return 8;
    else if (mod == 5) return 20;
    LL p;
    if (qpow(5, (mod-1)>>1, mod) == 1) p = mod - 1;
    else p = 2*(mod + 1);
    c = 0;
    for(LL i = 1; i * i <= p; ++i) if (p % i == 0) {
        LL x = i , y = p / i;
        F(x,mod);
        if (f1 == 0 && f2 == 1) return x;
        if (y != x) S[c++] = y;
    }
    while (c > 0) {
        F(S[--c],mod);
        if (f1 == 0 && f2 == 1) return S[c];
    }
    return 0;
}

int main() {
    int T;
    cin >> T;
    for (int Cas = 1; Cas <= T; ++Cas) {
        cin >> n;
        LL x = n;
        LL ans = 1;
        for(LL i = 2; i * i <= x; ++i) if (x % i == 0) {
            LL len = loop(i);
            LL S = 1;
            do x /= i, S = S * i;
            while (x % i == 0);
            S /= i; S = S * len;
            ans = lcm(ans,S);
        }
        if (x > 1) {
            LL len = loop(x);
            ans = lcm(ans, len);
        }
        if (ans % 2 == 0) ans /= 2;
        printf("Case #%d: %lld\n", Cas, ans);
    }
}
