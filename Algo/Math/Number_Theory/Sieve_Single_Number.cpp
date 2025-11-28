#include <bits/stdc++.h>

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
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

template<typename T> vector<pair<T, int>> factor(T n) {
    vector<pair<T, int>> fac;

    for(T i = 2; i * i <= n; i++){
        if(n % i) continue;
        fac.pb({i, 0});
        while(!(n % i))
            n /= i, fac.back().se++;
    }

    if(n > 1) fac.pb({n, 1});
    return fac;
}

template<typename T> vector<T> divisor(T n) {
    vector<T> D;

    for(int i = 1; i * i <= n; i++){
        if(n % i) continue;
        if(i * i != n) D.pb(n / i);
        D.pb(i);
    }
    
    sort(all(D));
    return D;
}

template<typename T> vector<pair<T, T>> divisor_pair(T n) {
    vector<pair<T, T>> D;
    vector<T> div = divisor(n);

    for(int i = 0, j = sz(div) - 1; i <= j; i++, j--)
        D.pb({div[i], div[j]});
    
    return D;
}

template<typename T>
bool perfect_square(T &n) {
    T s = sqrt(n);
    return s * s == n;
}

ll div_sum(ll n) {
    ll ans = n;

    for(ll p = 2, e; p * p <= n; p++){
        if(n % p) continue;
        e = 0;
        while(!(n % p))
            n /= p, e++;
        ans *= pow(p, e + 1) - 1; 
        ans /= p - 1;
    }

    return ans;
}

bool is_prime(ll n) {
    if(n < 2) return 0;
    if(n < 4) return 1;
    if(!(n % 2) || !(n % 3)) return 0;
    for(int i = 5; 1LL * i * i <= n; i += 6)
        if(!(n % i) || !(n % (i + 2)))
            return 0;
    return 1;
}

template<typename T> T phi(T &n) {
    T ans = n;
    for(int i = 2; i * i <= n; i++){
        if(n % i) continue;
        ans /= i, ans *= (i - 1);
        while(!(n % i)) n /= i;
    }

    if(n > 1) ans /= n, ans *= (n - 1);
    return ans;
}

int power(int a, int b, int m = MOD) {
    int c = 1;
    for(; b > 0; a = (1LL * a * a) % m, b >>= 1)
        if(b & 1) c = (1LL * c * a) % m;
    return c;
}

int inverse(int a, int m = MOD) {
    return power(a, m - 2);
}

int div_by_cnt(ll l, ll r, ll x) {
    return (r / x) - (l - 1) / x;
}

int main(){
 
    FastIO();
    debug(factor(918257364553));
    debug(factor(826446446281));
    debug(factor(1020267666889));

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
