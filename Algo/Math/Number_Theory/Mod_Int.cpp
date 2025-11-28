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
template<typename T, typename U>void prd(const pair<T, U>& v);
template<typename T, typename... Args>void prd(const T& v, Args... args);
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

template<const int &M = MOD> struct modi {
    int v;

    modi(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}

    friend modi power(modi a, ll b){modi c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend modi power(const modi &a, const modi b){return power(a, b.v);}
    // friend modi inverse(const modi &a){return power(a, M - 2);}

    modi& operator+=(const modi &b){v += b.v; if (v >= M) v -= M; return *this;}
    // modi& operator-=(const modi &b){v -= b.v; if (v < 0) v += M; return *this;}
    modi& operator*=(const modi &b){v = (ll)v * b.v % M; return *this;}
    // modi& operator/=(const modi &b){return *this *= inverse(b);}

    friend modi operator+(const modi &a, const modi &b){return modi(a) += b;}
    // friend modi operator-(const modi &a, const modi &b){return modi(a) -= b;}
    friend modi operator*(const modi &a, const modi &b){return modi(a) *= b;}
    // friend modi operator/(const modi &a, const modi &b){return modi(a) /= b;}
    
    friend ostream& operator<<(ostream& os, const modi &a){return os << a.v;}
    friend istream& operator>>(istream& is, modi &a){return is >> a.v; a = modi(a.v);}
};
using mint = modi<>;

int main(){
 
    FastIO();
    cout << power(mint(2), 100000).v;

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& v){cerr<<"(";prd(v.fi);cerr<<", ";prd(v.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& v, Args... args){prd(v);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
