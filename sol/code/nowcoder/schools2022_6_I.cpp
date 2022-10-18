#include <bits/stdc++.h>
using namespace std;
struct FAST_IO{
	FAST_IO(){
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
	}
}__fast_io;
#define all(a) (a).begin(),(a).end()
using ll=long long;
template<class T>
using vec=vector<T>;
#define FOR_TUPLE enableif_t<i!=tuple_size<T>::value>(1)
#define END_TUPLE enableif_t<i==tuple_size<T>::value>(1)

bool MULTIDATA=true;
template<class T,size_t n>
struct arr;

template<class T>
struct arr_dtype{using type=T;};
template<class T,size_t n>
struct arr_dtype<arr<T,n>>{using type=typename arr_dtype<T>::type;};
template<class T,size_t n>
struct arr:public array<T,n>{
  using array<T,n>::array;
  using dvalue_type=typename arr_dtype<T>::type;
  template<class ...Args>
  arr(T a,Args... args):array<T,n>{a,args...}{}
  template<class UT>
  arr(const arr<UT,n>& a){
    for (size_t i=0;i<n;i++)
      (*this)[i]=a[i];
  }
  #define TMP_ARR template<class AT=void,class T2,class TU=typename conditional<is_same<AT,void>::value,decltype(declval<T>()+declval<T2>()),AT>::type>
  #define op_arr(x) \
  TMP_ARR arr<T,n>& operator x##=(const arr<T2,n>& b){for (size_t i=0;i<n;i++) (*this)[i] x##=b[i];return *this;}\
  TMP_ARR arr<T,n>& operator x##=(const T2& b){for (size_t i=0;i<n;i++) (*this)[i] x##=b;return *this;}\
  TMP_ARR arr<TU,n> operator x(const arr<T2,n>& b)const{arr<TU,n> c=(*this);for (size_t i=0;i<n;i++) c[i] x##= b[i];return c;}\
  TMP_ARR arr<TU,n> operator x(const T2& b)const{arr<TU,n> c=(*this);for (size_t i=0;i<n;i++) c[i] x##=b;return c;}
  op_arr(+) op_arr(-) op_arr(*) op_arr(/)
};
template<class T>
using arr2=arr<T,2>;
template<class T>
using arr3=arr<T,3>;
template<class AT=void,class T,size_t d,class UT=typename conditional<is_same<AT,void>::value,T,AT>::type>
UT dot(const arr<T,d>& a,const arr<T,d>& b){
	UT c=0;
	for (auto& i:operator*<UT>(a,b)) c+=i;
	return c;
}
template<class AT=void,class T,size_t d,class UT=typename conditional<is_same<AT,void>::value,T,AT>::type>
UT _abs(const arr<T,d>& a){return sqrt(dot<UT>(a,a));}
template<class AT=void,class T,size_t d,class UT=typename conditional<is_same<AT,void>::value,T,AT>::type>
arr<UT,d> normalize(const arr<T,d>& a){return a/_abs<UT>(a);}
template<class T>
T crs(const arr2<T> &a,const arr2<T> &b){return a[0]*b[1]-a[1]*b[0];}
template<class T>
arr3<T> crs(const arr3<T> &a,const arr3<T> &b){return {a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]};}
vec<arr2<int>> s;
int n,d;
int main(){
  cin>>n>>d;
  vec<arr2<int>> v(n);
  for (auto& i:v) cin>>i[0]>>i[1];
  
  v.erase(unique(all(v)),v.end());
  for (int i=0;i<(int)v.size();i++)
    for (int j=i+1;j<(int)v.size();j++){
      if (crs(v[i],v[j])==0){
        v.erase(v.begin()+j);
        j--;
      }
    }
  for (int i=v.size()-1,d=1;i>=0;i--,d*=37) v[i]*=d;
  vec<arr2<int>> a={{0,0}};
  for (auto w:v){
    vec<arr2<int>> b;
    for (auto ai:a){
      for (int i=1;i<d;i++)
        b.push_back(ai+=w);
    }
    copy(all(b),back_inserter(a));
  }
  cout<<a.size()<<"\n";
  for (auto i:a) cout << i[0] << " " << i[1] << "\n";
}