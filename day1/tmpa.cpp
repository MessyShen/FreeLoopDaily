#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 15
#define MOD 1000000007

long long n = 5, m, k;
long long A0, AX, AY;
long long B0, BX, BY;


struct Mat {
    long long mat[MAXN][MAXN];
}A;

void init(){
    memset(A.mat, 0, sizeof(A.mat));
    A.mat[0][0] = A.mat[0][4] = AX*BX;
    A.mat[1][0] = A.mat[1][4] = AX*BY;
    A.mat[2][0] = A.mat[2][4] = AY*BX;
    A.mat[3][0] = A.mat[3][4] = AY*BY;
    A.mat[4][4] = A.mat[3][3] = 1;
    A.mat[1][1] = AX;
    A.mat[2][2] = BX;
    A.mat[3][1] = AY;
    A.mat[3][2] = BY;
}


Mat operator * (Mat a, Mat b){
    Mat c;
    memset(c.mat, 0 , sizeof(c.mat));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (a.mat[i][k] && b.mat[k][j]){
                    c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
                }
            }
        }
    }
    return c;
}

Mat operator ^ (Mat A, long long x){
    Mat c;
    memset(c.mat, 0 ,sizeof(c.mat));
    for (int i = 0; i < n; ++i){
        c.mat[i][i] = 1;
    }
    while (x){
        if (x & 1) {
            c = c * A;
        }
        A = A*A;
        x >>= 1;
    }
    return c;
}


int main(){
    long long t;
    while (cin >> t){
        //long long A0, AX, AY;
        //long long B0, BX, BY;
        cin >> A0 >> AX >> AY;
        cin >> B0 >> BX >> BY;
        init();
        Mat C;
        C = A^t;
        long long aa[5] = {A0*B0, A0, B0, 1, 0};
        for (int i = 0; i < 5; ++i){
            for (int j = 0; j < 5; ++j) {
                aa[i] = aa[i] * A.mat[i][j];
            }
        }
        cout << aa[4] << endl;
    }
}


