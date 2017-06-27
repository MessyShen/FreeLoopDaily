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

double pi = acos(-1.0);
double eps = 1e-6;

double Rm, R, r, x, y, vx, vy;

struct Point{
    double x, y;
}p;

pair<double, bool> InterCir(double r, double a, double b, double z, bool t = 0){
    double A = a*a + b*b;
    double B = -2*b*z;
    double C = z*z-r*r*a*a;
    int f = 1;
    //printf("%f\n",B*B - 4*A*C);
    if (B*B - 4*A*C < eps) {
        return make_pair(0, false);
    }
    if (t == 1) f = -1;
    return make_pair((-B + f * sqrt(B*B-4*A*C))/(2*A), true);
}

int main(){
    while (~scanf("%lf%lf%lf%lf%lf%lf%lf", &Rm, &R, &r, &x, &y, &vx, &vy)) {
        double a = vy;
        double b = -vx;
        double c = vy*x - vx*y;
        if (x * vx + y * vy > -eps) {
            printf("0\n");
            continue;
        }
        
        if (fabs(vy) < eps){
            double yy = y;
            double ans = 0;
            if (fabs(yy) < Rm + r){
                ans = 2 * fabs(sqrt((Rm + r)*(Rm + r)-y*y) - sqrt((R + r)*(R + r)-y*y));
            } else if (fabs(yy) < (R + r)){
                ans = 2 * fabs(sqrt((R + r)*(R + r)-y*y));
            } else {
                printf("0\n");
                continue;
            }
            ans /= fabs(vx);
            printf("%.3f\n", ans);
            continue;
        }
        pair<double, bool> pr1, pr2, pr3;
        pr1 = InterCir(r + Rm, a, b, c);
        pr2 = InterCir(r + R, a, b, c);
        pr3 = InterCir(r + R, a, b, c, 1);
        double yy = 0;
        if (pr1.second && pr2.second) {
            yy = 2 * fabs(pr1.first - pr2.first);
        } else if (pr1.second == 0 && pr2.second && pr3.second){
            yy = fabs(pr2.first - pr3.first);
        }
       // Point p1, p2;
        double ans;
        if (fabs(vx) < eps) {
            ans = yy;
        } else {
            ans = yy * sqrt(1 + vy * vy/(vx * vx)) / (vy/vx);
        }
        ans = fabs(ans / sqrt(vx*vx + vy*vy));
        if (fabs(ans) < eps) {
            printf("0\n");
        } else printf("%.3f\n", ans);
    }
}
