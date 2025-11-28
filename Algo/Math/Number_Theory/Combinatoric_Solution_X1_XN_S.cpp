#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) (x).erase(unique(all(x)), (x).end());
#define all_range(x) sort(all(x)), (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& value);
template<typename T, typename... Args>void prd(const T& value, Args... args);
template<typename... Args>void debug(Args... args);
template<typename K, typename V>void debug(const map<K, V>& c);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

template<const int &M = MOD> struct mod_int {
    int val;

    mod_int(ll v = 0) {if(v < 0) v = v % M + M; if(v >= M) v %= M; val = v;}

    friend mod_int power(mod_int a, ll b){mod_int c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend mod_int power(const mod_int &a, const mod_int b){return power(a, b.val);}
    friend mod_int inverse(const mod_int &a){return power(a, M - 2);}

    mod_int& operator+=(const mod_int &b){val += b.val; if (val >= M) val -= M; return *this;}
    mod_int& operator-=(const mod_int &b){val -= b.val; if (val < 0) val += M; return *this;}
    mod_int& operator*=(const mod_int &b){val = (ll)val * b.val % M; return *this;}
    mod_int& operator/=(const mod_int &b){return *this *= inverse(b);}
    mod_int& operator++(){val = val == M - 1 ? 0 : val + 1; return *this;}
    mod_int& operator--(){val = val == 0 ? M - 1 : val - 1; return *this;}
    mod_int operator++(int){mod_int a = *this; ++*this; return a;}
    mod_int operator--(int){mod_int a = *this; --*this; return a;}

    friend mod_int operator-(const mod_int &a){return 0 - a;}
    friend mod_int operator!(const mod_int &a){return a.val != 0;}
    friend mod_int operator+(const mod_int &a, const mod_int &b){return mod_int(a) += b;}
    friend mod_int operator-(const mod_int &a, const mod_int &b){return mod_int(a) -= b;}
    friend mod_int operator*(const mod_int &a, const mod_int &b){return mod_int(a) *= b;}
    friend mod_int operator/(const mod_int &a, const mod_int &b){return mod_int(a) /= b;}
    
    friend bool operator==(const mod_int &a, const mod_int &b){return a.val == b.val;}
    friend bool operator!=(const mod_int &a, const mod_int &b){return a.val != b.val;}
    friend bool operator>=(const mod_int &a, const mod_int &b){return a.val >= b.val;}
    friend bool operator<=(const mod_int &a, const mod_int &b){return a.val <= b.val;}
    friend bool operator>(const mod_int &a, const mod_int &b){return a.val > b.val;}
    friend bool operator<(const mod_int &a, const mod_int &b){return a.val < b.val;}
    
    friend ostream& operator<<(ostream& os, const mod_int &a){return os << a.val;}
    friend istream& operator>>(istream& is, mod_int &a){return is >> a.val; a = mod_int(a.val);}
};
using mint = mod_int<>;

using poly = vector<mint>;

mint eval(poly a, mint x) {
    mint ans = 0, p = 1;
    for(mint b : a){
        ans += p * b;
        p *= x;
    }
    return ans;
}
poly operator+(poly a, poly b) {
    if(sz(a) < sz(b)) a.resize(sz(b), 0);
    for(int i = 0; i < sz(b); i++) 
        a[i] += b[i];
    return a;
} 

poly operator-(poly a, poly b) {
    if(sz(a) < sz(b)) a.resize(sz(b), 0);
    for(int i = 0; i < b.size(); i++) 
        a[i] -= b[i];
    return a;
}

poly operator*(poly a, poly b) {
    poly r(a.size() + b.size() - 1, 0);
    for(int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++) 
           r[i + j] += a[i] * b[j];
    return r;
}

vector<pair<ll, int>> get(vector<ll> a) {
  int n = sz(a);
  vector<pair<ll, int>> ans;

  for(int mask = 0; mask < (1 << n); mask++){
    ll add = 0; 
    int x = 1;

    for(int i = 0; i < n; i++){
        if(mask >> i & 1){
            add += a[i];
            x = -x;
        }
    }

    ans.pb({add, x});
  }

  return ans;
}

// (x + n)(x + n - 1)...(x + n - k + 1);
poly falling(ll n, int k) {
  poly ans({1});
  mint p = n;

  for(int i = 0; i < k; i++)
    ans = ans * poly({p - i, 1});

  return ans;
}

// return the number of solution to the equation
// x[1] + ... + x[n] = s, where 0 <= x[i] <= a[i]
// in O(2 ^ (n / 2) * n^2)

mint calc(vector<ll> &A, ll s) {
    int n = sz(A);
    for(auto &a : A) a++;
    vector<ll> l, r;

    for(int i = 0; i < n; i++){
        if(i & 1) r.pb(A[i]);
        else l.pb(A[i]);
    }

    auto L = get(l);
    auto R = get(r);

    sort(all(L));
    sort(All(R));

    int j = 0; 
    poly f({0});
    mint ans = 0;

    for(auto &[x, y] : R){
        for(;j < sz(L) && L[j].fi + x <= s; j++){
            if(L[j].se == 1)
                f = f + falling(s + n - 1 - L[j].fi, n - 1);
            else 
                f = f - falling(s + n - 1 - L[j].fi, n - 1);
        }

        ans += eval(f, mint(x)) * y;
    }

    for(int i = 1; i <= n - 1; i++)
        ans /= i;
    
    return ans;
}

int main(){
 
    FastIO();
    mint n; cin >> n;
    n += 1;
    cout << n;

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& value){cerr<<"(";prd(value.first);cerr<<", ";prd(value.second);cerr<<")";}
template<typename T, typename... Args>void prd(const T& value, Args... args){prd(value);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr << "]\n";}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c) { for (const auto &v : c) debug(v); cerr << '\n';}
