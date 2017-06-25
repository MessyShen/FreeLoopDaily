/*
f[i][j]表示第j位是不是字符i
g[i][j][k]表示考虑询问串前i位，失配不超过j次，是否可以匹配到S的k位置

g[i][j][k]=g[i-1][j-1][k-1]|(g[i-1][j][k-1]&f[T[i]][k])

for(i=1;i<=len_T;i++){
  x=T[i];
  for(j=3;j;j--){
    g[j]<<=1;
    g[j]&=f[x];
    g[j]|=g[j-1];
  }
  g[0]<<=1;
  g[0]&=f[x];
}
*/
#include<cstdio>
#include<cstring>
typedef unsigned long long ll;
const int N=50005,M=N/64+5;
const ll FULL=~0ULL;
int Case,n,m,len,lim,i,l,r,k,w[65536],tag[M];char a[N],b[N],op[9];
inline int popcount(ll x){return w[x&65535]+w[x>>16&65535]+w[x>>32&65535]+w[x>>48];}
struct BIT{
  ll v[M];
  void clr(){for(int i=0;i<=lim;i++)v[i]=0;}
  void full(){for(int i=0;i<=lim;i++)v[i]=FULL;}
  int get(int x){return v[x>>6]>>(x&63)&1;}
  void flip(int x){v[x>>6]^=1ULL<<(x&63);}
  int ask(int l,int r){
    int x=l>>6,y=r>>6,t=0,i;
    if(x==y){
      for(i=l;i<=r;i++)if(get(i))t++;
      return t;
    }
    for(i=l;(i>>6)==x;i++)if(get(i))t++;
    for(i=r;(i>>6)==y;i--)if(get(i))t++;
    for(i=x+1;i<y;i++)t+=popcount(v[i]);
    return t;
  }
}f[4],g[10];
inline int get(int x){return (a[x]+tag[x>>6])%10;}
inline void change(int l,int r,int k){
  int x=l>>6,y=r>>6,i,o;
  if(x==y){
    for(i=l;i<=r;i++){
      o=get(i);
      g[(o-tag[x]+10)%10].flip(i);
      g[(o-tag[x]+10+k)%10].flip(i);
      (a[i]+=k)%=10;
    }
    return;
  }
  for(i=l;(i>>6)==x;i++){
    o=get(i);
    g[(o-tag[x]+10)%10].flip(i);
    g[(o-tag[x]+10+k)%10].flip(i);
    (a[i]+=k)%=10;
  }
  for(i=r;(i>>6)==y;i--){
    o=get(i);
    g[(o-tag[y]+10)%10].flip(i);
    g[(o-tag[y]+10+k)%10].flip(i);
    (a[i]+=k)%=10;
  }
  for(i=x+1;i<y;i++)(tag[i]+=k)%=10;
}
inline void up(int k){
  ll t;
  for(int i=lim;i;i--){
    f[0].v[i]=(f[0].v[i]<<1)+(f[0].v[i-1]>>63);
    f[1].v[i]=(f[1].v[i]<<1)+(f[1].v[i-1]>>63);
    f[2].v[i]=(f[2].v[i]<<1)+(f[2].v[i-1]>>63);
    f[3].v[i]=(f[3].v[i]<<1)+(f[3].v[i-1]>>63);
    t=g[(k-tag[i]+10)%10].v[i];
    f[3].v[i]=(f[3].v[i]&t)|f[2].v[i];
    f[2].v[i]=(f[2].v[i]&t)|f[1].v[i];
    f[1].v[i]=(f[1].v[i]&t)|f[0].v[i];
    f[0].v[i]&=t;
  }
  f[0].v[0]<<=1;
  f[1].v[0]<<=1;
  f[2].v[0]<<=1;
  f[3].v[0]<<=1;
  t=g[(k-tag[0]+10)%10].v[0];
  f[3].v[0]=(f[3].v[0]&t)|f[2].v[0];
  f[2].v[0]=(f[2].v[0]&t)|f[1].v[0];
  f[1].v[0]=(f[1].v[0]&t)|f[0].v[0];
  f[0].v[0]&=t;
}
int main(){
  for(i=1;i<65536;i++)w[i]=w[i>>1]+(i&1);
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d%s",&n,&m,a+1);
    lim=n/64;
    for(i=0;i<10;i++)g[i].clr();
    for(i=1;i<=n;i++)g[a[i]-='0'].flip(i);
    for(i=0;i<=lim;i++)tag[i]=0;
    while(m--){
      scanf("%s%d%d",op,&l,&r);
      if(op[0]=='+'){
        scanf("%d",&k);
        change(l,r,k);
      }else{
        scanf("%s",b);
        len=strlen(b);
        if(len>r-l+1){puts("0");continue;}
        f[0].full();
        f[1].full();
        f[2].full();
        f[3].full();
        for(i=0;i<len;i++)up(b[i]-'0');
        printf("%d\n",f[3].ask(l+len-1,r));
      }
    }
  }
  return 0;
}
