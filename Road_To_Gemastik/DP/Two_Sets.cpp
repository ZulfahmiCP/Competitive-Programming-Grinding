#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define uniq(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'
#define ttm template
#define ttp typename

using namespace std;
ttm<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}

ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cm = 1;}cerr<<"]\n";}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

template<const int &M = MOD> struct modi {
    int v;

    modi(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}

    friend modi power(modi a, ll b){modi c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend modi power(const modi &a, const modi b){return power(a, b.v);}
    friend modi inverse(const modi &a){return power(a, M - 2);}

    modi& operator+=(const modi &b){v += b.v; if (v >= M) v -= M; return *this;}
    modi& operator-=(const modi &b){v -= b.v; if (v < 0) v += M; return *this;}
    modi& operator*=(const modi &b){v = (ll)v * b.v % M; return *this;}
    modi& operator/=(const modi &b){return *this *= inverse(b);}

    friend modi operator+(modi a, modi b){return modi(a) += b;}
    friend modi operator-(modi a, modi b){return modi(a) -= b;}
    friend modi operator*(modi a, modi b){return modi(a) *= b;}
    friend modi operator/(modi a, modi b){return modi(a) /= b;}
    
    friend bool operator==(const modi &a, const modi &b){return a.v == b.v;}
    friend bool operator!=(const modi &a, const modi &b){return a.v != b.v;}
    friend bool operator>=(const modi &a, const modi &b){return a.v >= b.v;}
    friend bool operator<=(const modi &a, const modi &b){return a.v <= b.v;}
    friend bool operator>(const modi &a, const modi &b){return a.v > b.v;}
    friend bool operator<(const modi &a, const modi &b){return a.v < b.v;}
    
    friend ostream& operator<<(ostream& os, const modi &a){return os << a.v;}
    friend istream& operator>>(istream& is, modi &a){return is >> a.v; a = modi(a.v);}
};
using mint = modi<>;

int main() {

    FastIO();
    int n; cin >> n;
    int m = n * (n + 1) / 2;

    if(m & 1){
        cout << "0\n";
        return 0;
    }
    

    m /= 2;
    vector<mint> dp(m + 1, 0);

    dp[0] = 1;

    for(int j = 1; j <= n; j++)
        for(int i = m; i >= j; i--)
            dp[i] += dp[i - j];

    cout << dp[m] / 2 << endl;
    
    return 0;
}
