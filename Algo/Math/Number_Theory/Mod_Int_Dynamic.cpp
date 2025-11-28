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

struct mint {
    int val;

    mint(ll v = 0) {if(v < 0) v = v % mod + mod; if(v >= mod) v %= mod; val = v;}

    friend mint power(mint a, ll b){mint c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend mint power(const mint &a, const mint b){return power(a, b.val);}
    friend mint inv(const mint &a){return power(a, mod - 2);}

    mint& operator+=(const mint &b){val += b.val; if (val >= mod) val -= mod; return *this;}
    mint& operator-=(const mint &b){val -= b.val; if (val < 0) val += mod; return *this;}
    mint& operator*=(const mint &b){val = (ll)val * b.val % mod; return *this;}
    mint& operator/=(const mint &b){return *this *= inv(b);}
    mint& operator++(){val = val == mod - 1 ? 0 : val + 1; return *this;}
    mint& operator--(){val = val == 0 ? mod - 1 : val - 1; return *this;}
    mint operator++(int){mint a = *this; ++*this; return a;}
    mint operator--(int){mint a = *this; --*this; return a;}

    friend mint operator!(const mint &a){return a.val != 0;}
    friend mint operator-(const mint &a){return 0 - a;}
    friend mint operator+(const mint &a, const mint &b){return mint(a) += b;}
    friend mint operator-(const mint &a, const mint &b){return mint(a) -= b;}
    friend mint operator*(const mint &a, const mint &b){return mint(a) *= b;}
    friend mint operator/(const mint &a, const mint &b){return mint(a) /= b;}
    
    friend bool operator==(const mint &a, const mint &b){return a.val == b.val;}
    friend bool operator!=(const mint &a, const mint &b){return a.val != b.val;}
    friend bool operator>=(const mint &a, const mint &b){return a.val >= b.val;}
    friend bool operator<=(const mint &a, const mint &b){return a.val <= b.val;}
    friend bool operator>(const mint &a, const mint &b){return a.val > b.val;}
    friend bool operator<(const mint &a, const mint &b){return a.val < b.val;}
    
    friend std::ostream& operator<<(std::ostream& os, const mint &a){return os << a.val;}
    friend std::istream& operator>>(std::istream& is, mint &a){return is >> a.val; a = mint(a.val);}
};

int main(){
 
    FastIO();
    

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
