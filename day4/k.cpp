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

typedef long long lint;

int c[30];
int N;
int ans = 0;

int calcColor(){
    int res = 0;
    if (c[0] == c[1] && c[0] == c[2] && c[0] == c[3]){
        res ++;
    }
    if (c[4] == c[5] && c[4] == c[10] && c[4] == c[11]) {
        res++;
    }
    if (c[16] == c[17] && c[16] == c[18] && c[18] == c[19]) {
        res ++;
    }
    if (c[6] == c[7] && c[6] == c[12] && c[6] == c[13]) {
        res ++;
    }
    if (c[8] == c[9] && c[8] == c[14] && c[8] == c[15]) {
        res++;
    }
    if (c[21] == c[20] && c[21] == c[22] && c[21] == c[23]) {
        res++;
    }
    return res;
}

void R(){
    int t = c[1];
    int s = c[3];
    c[1]  = c[7];
    c[3]  = c[13];
    c[7]  = c[17];
    c[13] = c[19];
    c[17] = c[21];
    c[19] = c[23];
    c[21] = t;
    c[23] = s;
    
    t     = c[8];
    c[8]  = c[14];
    c[14] = c[15];
    c[15] = c[9];
    c[9]  = t;
}

void R2(){
    int t = c[1];
    int s = c[3];
    c[1]  = c[21];
    c[3]  = c[23];
    c[21] = c[17];
    c[23] = c[19];
    c[17] = c[7];
    c[19] = c[13];
    c[7]  = t;
    c[13] = s;
    
    t     = c[8];
    c[8]  = c[9];
    c[9]  = c[15];
    c[15] = c[14];
    c[14] = t;
    
}


void U(){
    int t = c[2];
    int s = c[3];
    c[2]  = c[11];
    c[3]  = c[5];
    c[11] = c[17];
    c[5]  = c[16];
    c[17] = c[8];
    c[16] = c[14];
    c[8]  = t;
    c[14] = s;
    
        t = c[6];
    c[6]  = c[12];
    c[12] = c[13];
    c[13] = c[7];
    c[7]  = t;
}

void U2(){
    int t = c[2];
    int s = c[3];
    c[2]  = c[8];
    c[3]  = c[14];
    c[8]  = c[17];
    c[14] = c[16];
    c[17] = c[11];
    c[16] = c[5];
    c[11] = t;
    c[5]  = s;
    
    t = c[6];
    c[6]  = c[7];
    c[7]  = c[13];
    c[13] = c[12];
    c[12] = t;
}


void F(){
    int t = c[10];
    int s = c[11];
    c[10] = c[21];
    c[11] = c[20];
    c[21] = c[14];
    c[20] = c[15];
    c[14] = c[12];
    c[15] = c[13];
    c[12]  = t;
    c[13] = s;
    
    t = c[16];
    c[16]  = c[18];
    c[18] = c[19];
    c[19] = c[17];
    c[17]  = t;
}

void F2(){
    int t = c[10];
    int s = c[11];
    c[10] = c[12];
    c[11] = c[13];
    c[12]  = c[14];
    c[13] = c[15];
    c[14] = c[21];
    c[15] = c[20];
    c[21] = t;
    c[20] = s;
    
    t = c[16];
    c[16]  = c[17];
    c[17] = c[19];
    c[19] = c[18];
    c[18]  = t;
}


void dfs(int n){
    int t = calcColor();
    if (t > ans) {
        ans =  t;
    }
    if (n == 0) {
        return;
    }
    R();  dfs(n-1); R2();
    R2(); dfs(n-1); R();
    F();  dfs(n-1); F2();
    F2(); dfs(n-1); F();
    U();  dfs(n-1); U2();
    U2(); dfs(n-1); U();
}

int main(){
    while(~scanf("%d", &N)){
        ans = 0;
        for (int i = 0; i < 24; ++i) {
            scanf("%d", &c[i]);
        }
        dfs(N);
        printf("%d\n", ans);
    }
    
}
