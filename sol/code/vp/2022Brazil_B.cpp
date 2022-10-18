// Problem: B. Fun with Stones
// Contest: Codeforces - 2022-2023 ICPC Brazil Subregional Programming Contest
// URL: https://codeforces.com/gym/103960/problem/B
// Memory Limit: 1024 MB
// Time Limit: 250 ms
// 
// Powered by CP Editor (https://cpeditor.org)
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
struct FAST_IO{
	FAST_IO(){
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
	}
}__fast_io;
int DP[40][30];
int ways[]={0,3,5,6};
int x,y;
int gn(int x,int y,int z){
  return (x^y)&x|~(x^y)&z;
}
constexpr int MOD=1000000000+7;
int power(int x,int y){
  if (y==0) return 1;
  if (y&1)
    return (ll)x*power((ll)x*x%MOD,y>>1)%MOD;
  return power((ll)x*x%MOD,y>>1);
}

ll dfs(int x,int y,int z){//f=true < f=false ==
  memset(DP,0,sizeof(DP));
  DP[0][0]=1;
  for (int i=0;i<32;i++){
    int xi=(x>>i)&1,yi=(y>>i)&1,zi=(z>>i)&1;
    int c=xi*4+yi*2+zi;
    for (auto way:ways)
      for (int j=0;j<8;j++){
        (DP[i+1][gn(way,c,j)]+=DP[i][j])%=MOD;
      }
  }
  return DP[32][0];
}
int main(){
  int l1,r1,l2,r2,l3,r3;
  cin>>l1>>r1>>l2>>r2>>l3>>r3;
  l1--;l2--;l3--;
  ll ans=dfs(r1,r2,r3)
  -dfs(l1,r2,r3)-dfs(r1,l2,r3)-dfs(r1,r2,l3)
  +dfs(l1,l2,r3)+dfs(l1,r2,l3)+dfs(r1,l2,l3)
  -dfs(l1,l2,l3);
  ans%=MOD;
  if (ans<0) ans+=MOD;
  ll a=1;
  (a*=r1-l1)%=MOD;
  (a*=r2-l2)%=MOD;
  (a*=r3-l3)%=MOD;
  cout << (MOD+1-ans*power(a,MOD-2)%MOD)%MOD << endl;
}