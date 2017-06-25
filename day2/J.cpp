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
 �����⡿
 ����n��30��������ÿ�����ĳ���Ҳ������30��
 Alice��Bob���ģ�Alice���֣���ʼ�ǿմ���
 ÿ��Ҫ�ڴ�ǰ�򴮺������һ��Сд�ַ���ʹ��ԭʼ���У����ٴ���һ�����������Ӵ������ܲ��������ˡ�
 ˫�����ĵĹؼ����ǣ�ʤ�ܣ��Լ����������ܸߣ����ַ��������ܵͣ�
 �������Alice�����Ž�֡�
 
 ��������
 ֱ�Ӱ��ջ���SG���ĵķ���������ֹ̬�˻س�ʼ̬���մ����ͺ���!
 ���Կ���������ôд�ģ��õ��˺ܶ�С���ɡ�
 ��Ԥ��������кϷ������ٰ���������õ�DP��˳��
 ����ֱ����DP����ôд20���Ӿ�д��1A����
 
 ��ʱ�临�Ӷ�&&�Ż���
 O(n^3 * log(n^3) )
 
 */
