#include <bits/stdc++.h>
using namespace std;
int v[1000000+10];
int vi[1000000+10];
constexpr int N=1<<19;
int a[N+1];
int main(){
  int n;
  cin>>n;
  for (int i=1;i<=n;i++){
    cin>>v[i];
    v[i]=1<<(int)log2(v[i]);
    vi[i]=i;
  }
  sort(vi+1,vi+1+n,[](int i,int j){
    return v[i]<v[j];
  });
  int j=1;
  for (int i=1;i<=n;i++){
    int va=v[vi[i]];
    while (a[j]) j++;
    for (int k=j;k<N;k+=va){
      a[k]=vi[i];
    }
  }
  cout << N << endl;
  for (int i=1;i<=N;i++)
    cout << max(a[i],1) << " ";
}