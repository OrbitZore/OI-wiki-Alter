#include <bits/stdc++.h>
using namespace std;
struct FAST_IO {
  FAST_IO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  }
} __fast_io;
#define all(a) (a).begin(), (a).end()
auto& _ = std::ignore;
using ll = long long;
template <class T>
using vec = vector<T>;

bool MULTIDATA = true;
#ifndef __OP__
#define __OP__
#define def_op(op)                                  \
  this_type operator op(const this_type& a) const { \
    this_type k(*this);                             \
    k op## = a;                                     \
    return k;                                       \
  }
#define def_cmp(op, n2)                        \
  bool operator op(const this_type& a) const { \
    return n2 op a.n2;                         \
  }
#define def_all_cmp(n2)                                         \
  def_cmp(<, n2) def_cmp(>, n2) def_cmp(<=, n2) def_cmp(>=, n2) \
      def_cmp(!=, n2) def_cmp(==, n2)
#endif
#define ATL_MATH
constexpr ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}
constexpr ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}
template <class T>
T power(T a, size_t b, const T& unit = 1) {
  if (b == 0)
    return unit;
  if (b & 1)
    return a * power(a * a, b >> 1, unit);
  return power(a * a, b >> 1, unit);
}
constexpr ll ceildiv(const ll a, const ll b) {
  return a / b + (a % b ? 1 : 0);
}
tuple<ll, ll, ll> exgcd(ll a, ll b) {  // a1+b2=gcd(a,b)
  if (b == 0)
    return make_tuple(a, 1, 0);
  ll g, x, y;
  tie(g, x, y) = exgcd(b, a % b);
  return make_tuple(g, y, x - a / b * y);
}
tuple<ll, ll, ll> Fexgcd(ll a, ll b) {  // a1+b2=gcd(a,b),ensure 1>0
  auto k = exgcd(a, b);
  if (get<1>(k) < 0) {
    get<1>(k) += b;
    get<2>(k) -= a;
  }
  return k;
}
template <class T, class uT, ll mod>
struct _mint {
  using this_type = _mint;
  T v;
  _mint() = default;
  template <class iT>
  constexpr _mint(const iT& a) {
    v = a % mod;
    v += v < 0 ? mod : 0;
  }
  template <class iT>
  static _mint from(const iT& v) {
    _mint a;
    a.v = v;
    return a;
  }
  _mint& operator+=(const _mint& a) {
    return (v += a.v) >= mod && (v -= mod), *this;
  }
  _mint& operator-=(const _mint& a) {
    return (v -= a.v) < 0 && (v += mod), *this;
  }
  _mint& operator*=(const _mint& a) { return (v = ((uT)v * a.v) % mod), *this; }
  def_op(+) def_op(-) def_op(*) def_all_cmp(v)
#ifdef ATL_MATH
      _mint inverse() const {
    auto c = exgcd(v, mod);
    _mint s;
    s.v = get<1>(c) < 0 ? get<1>(c) + mod : get<1>(c);
    return s;
  }
  _mint& operator/=(const _mint& a) {
    return (*this) *= a.inverse(), *this;
  }
  def_op(/)
#endif
};
template <class T, class uT, ll mod>
ostream& operator<<(ostream& os, const _mint<T, uT, mod>& a) {
  return os << a.v;
}
template <class T, class uT, ll mod>
istream& operator>>(istream& os, _mint<T, uT, mod>& a) {
  T k;
  os >> k;
  a = _mint<T, uT, mod>(k);
  return os;
}
using mint = _mint<int, long long, 998244353>;
using mll = _mint<long long, __int128, 998244353>;

template <class T>
struct ntt {
  constexpr static int l = 16, n = 1 << 16;
  array<int, n> r{};
  const int mod{998244353};
  const array<const T, 2> P{3, 332748118};
  array<array<T, n>, 2> W{};
  int floorintlog2(int i) {
    int k = 0;
    while (i)
      i >>= 1, k++;
    cout << k << endl;
    return k;
  }
  ntt() {
    for (int i = 0; i < n; i++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    for (int type : {0, 1})
      for (int i = 0; i < l; i++)
        W[type][i] = power(P[type], (mod - 1) / (1 << i << 1));
  }
  template <int type, class U>
  valarray<T> _NTT(const U& B) const {
    valarray<T> A(n);
    copy(std::begin(B), std::end(B), begin(A));
    for (int i = 0; i < n; i++)
      if (i < r[i])
        swap(A[i], A[r[i]]);
    for (int mid = 1, midj = 0; mid < n; mid <<= 1, midj++) {
      T Wn = W[type][midj];
      for (int R = mid << 1, j = 0; j < n; j += R) {
        T w = T::from(1);
        for (int k = 0; k < mid; k++, w *= Wn) {
          const T x = A[j + k], y = w * A[j + mid + k];
          A[j + k] = x + y;
          A[j + mid + k] = x - y;
        }
      }
    }
    if (type)
      A *= power(T(n), mod - 2);
    return A;
  }
  template <class U>
  valarray<T> NTT(const U& A) const {
    return _NTT<0>(A);
  }
  valarray<T> DNT(const valarray<T>& A) const { return _NTT<1>(A); }
};
template <class T>
struct RANGE_ {
  T b, e;
  T begin() const& { return b; };
  T end() const& { return e; };
};
template <class T>
RANGE_<T> RANGE(T a, T b) {
  return RANGE_<T>{a, b};
}

#define N (50000 + 10)
mint P[10000000 + 10] = {1}, NIP[N] = {-1}, IP[10000000 + 10];
int w;
int c[100];
ntt<mint> G;
array<valarray<mint>, 11> cv, f;
int C, LC;
#define NN (10000000 / 2 + 1)
mint expa(int a, int i) {
  if (a == 0)
    return i == 0 ? 1 : 0;
  return IP[i];
}

int main() {
  for (mint i = 1; i.v <= 10000000; i.v++) {
    P[i.v] = P[i.v - 1] * i;
  }
  for (int i = 1; i < N; i++)
    NIP[i] = NIP[0] / P[i];
  for (int i = 0; i <= 10000000; i++) {
    IP[i] = P[i].inverse();
  }
  cin >> w;
  for (int i = 0; i < w; i++)
    cin >> c[i];
  f.fill(valarray<mint>(0, N));
  f[0][0] = 1;
  for (int i = 0; i < w; i++) {
    cv[i] = G.NTT(RANGE(&NIP[0], &NIP[c[i]]));
  }
  for (int i = 0; i < w; i++) {
    for (int j = w; j >= 1; j--) {
      f[j] = f[j - 1] + G.DNT(G.NTT(f[j]) * cv[i]);
    }
    f[0] = G.DNT(G.NTT(f[0]) * cv[i]);
  }
  int q;
  cin >> q;
  while (q--) {
    int n;
    cin >> n;
    mint ans = 0;
    int nn = min(n, 50000);
    for (int j = 0; j <= w; j++) {
      mint k = power(mint(j), n - nn);
      for (int i = nn; i >= 0; i--) {
        ans += f[j][i] * k * IP[n - i];
        k *= j;
      }
    }
    cout << ans * P[n] << endl;
  }
}