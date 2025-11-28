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

    friend modi operator-(const modi &a){return 0 - a;}
    friend modi operator+(const modi &a, const modi &b){return modi(a) += b;}
    friend modi operator-(const modi &a, const modi &b){return modi(a) -= b;}
    friend modi operator*(const modi &a, const modi &b){return modi(a) *= b;}
    friend modi operator/(const modi &a, const modi &b){return modi(a) /= b;}
    
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
    int m,n; cin >> m >> n;
    
    if(m == 1){
        vector<vector<mint>> dp(n, vector<mint>(3));
        // dp[i][0] = bolong \
        // dp[i][1] = bolong /
        // dp[i][2] = full

        dp[0][0] = 1;
        dp[0][1] = 1;
        dp[0][2] = 2;

        for(int i = 1; i < n; i++){
            dp[i][0] = dp[i-1][1] + dp[i-1][2]; 
            dp[i][1] = dp[i-1][0] + dp[i-1][2];
            dp[i][2] = dp[i][0] + dp[i][1];
        }

        cout << dp[n - 1][2] << endl;
    } else {
        vector<vector<mint>> dp(n, vector<mint>(5));

        dp[0][0] = 2;
        dp[0][1] = 1;
        dp[0][2] = 1;
        dp[0][3] = 1;
        dp[0][4] = 6;

        for(int i = 1; i < n; i++){
            dp[i][0] = 3 * dp[i-1][2] + 2 * dp[i-1][4] + dp[i-1][1] + dp[i-1][3];
            dp[i][1] = 3 * dp[i-1][3] +     dp[i-1][4] + dp[i-1][0] + dp[i-1][2];
            dp[i][2] = 3 * dp[i-1][0] +     dp[i-1][4] + dp[i-1][1] + dp[i- 1][3];
            dp[i][3] = 3 * dp[i-1][1] +     dp[i-1][4] + dp[i-1][0] + dp[i-1][2];
            dp[i][4] = dp[i][0] + dp[i][1] + 2 * dp[i][2] + dp[i][3];
        }

        cout << dp[n-1][4] << endl;
    }
    
    return 0;
}
