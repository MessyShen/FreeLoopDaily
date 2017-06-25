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
void fre() { freopen("c://test//input.in", "r", stdin); freopen("c://test//output.out", "w", stdout); }
#define MS(x, y) memset(x, y, sizeof(x))
#define ls o<<1
#define rs o<<1|1
typedef long long LL;
typedef unsigned long long UL;
typedef unsigned int UI;
template <class T1, class T2>inline void gmax(T1 &a, T2 b) { if (b > a)a = b; }
template <class T1, class T2>inline void gmin(T1 &a, T2 b) { if (b < a)a = b; }
const int N = 0, M = 0, Z = 1e9 + 7, inf = 0x3f3f3f3f;
template <class T1, class T2>inline void gadd(T1 &a, T2 b) { a = (a + b) % Z; }
int casenum, casei;
int n;
char s[32];
struct A{
    int win;
    int me;
    int enemy;
    bool operator > (const A & b) {
        if (win != b.win)return win > b.win;
        if (me != b.me)return me > b.me;
        return enemy < b.enemy;
    }
    
    A Ene(int sco) {
        return { 1 - win, enemy + sco, me };
    }
};
map<string, A> mop;
map<string, int> occ;
map<string, int> dfn;
int score(string s) {
    int ret = 0;
    int mx = 0;
    for (int i = 0, sz = s.size(); i < sz; ++i) {
        ret += (s[i] - 'a' + 1);
        gmax(mx, s[i] - 'a' + 1);
    }
    return ret * mx + occ[s];
}

bool cmp(string a, string b) {
    return a.size() < b.size();
}

int main() {
    while (~scanf("%d", &n))
    {
        mop.clear(); occ.clear(); dfn.clear();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s);
            for (int l = 0; s[l]; ++l) {
                for (int r = l; s[r]; ++r){
                    char tmp = s[r + 1]; s[r + 1] = 0;
                    if (dfn[s + l] != i) {
                        dfn[s + l] = i;
                        ++occ[s + l];
                    }
                    s[r + 1] = tmp;
                }
            }
        }
        
        vector<string> vt;
        for (auto it : occ) vt.push_back(it.first);
        vt.push_back("");
        sort(vt.begin(), vt.end(), cmp);
        for (int i = vt.size() - 1; ~i; --i) {
            string s = vt[i];
            A now = { 0, 0, 0 };
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                if (mop.count(s + ch)) {
                    gmax(now, mop[s + ch].Ene(score(s + ch)));
                }
                if (mop.count(ch + s)) {
                    gmax(now, mop[ch + s].Ene(score(ch + s)));
                }
            }
            mop[s] = now;
        }
        auto it = mop[""];
        printf("%s\n", it.win == 1 ? "Alice" : "Bob");
        printf("%d %d\n", it.me, it.enemy);
    }
    return 0;
}
/*
 【题意】
 给你n（30）个串，每个串的长度也不超过30。
 Alice和Bob博弈，Alice先手，初始是空串。
 每次要在串前或串后任意加一个小写字符，使得原始串中，至少存在一个串包含该子串。不能操作就输了。
 双方博弈的关键字是（胜败，自己分数尽可能高，对手分数尽可能低）
 让你输出Alice的最优结局。
 
 【分析】
 直接按照基本SG博弈的方法，从终止态退回初始态（空串）就好啦!
 可以看看我是怎么写的，用到了很多小技巧。
 先预处理好所有合法串，再按长度排序得到DP的顺序。
 接着直接做DP，这么写20分钟就写完1A啦！
 
 【时间复杂度&&优化】
 O(n^3 * log(n^3) )
 
 */
