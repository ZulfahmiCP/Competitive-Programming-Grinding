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
 
#ifndef ONLINE_JUDGE
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}
ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<"[ ";for(auto v:c){prd(v);cerr<<' ';}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<"[ ";for(auto v:c){cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cerr<<' ';}cerr<<"]\n";}
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

template<const int &M = MOD> struct modi {
    int v;
    
    modi(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}

    friend modi power(modi a, ll b) {modi c(1); for(; b > 0; a *= a, b >>= 1) if(b & 1) c *= a; return c;}
    friend modi inverse(const modi &a) {return power(a, M - 2);}

    modi& operator+=(const modi &b) {v += b.v; if(v >= M) v -= M; return *this;}
    modi& operator-=(const modi &b) {v -= b.v; if(v < 0) v += M; return *this;}
    modi& operator*=(const modi &b) {v = (ll)v * b.v % M; return *this;}
    modi& operator/=(const modi &b) {v *= inverse(b); return *this;}
    
    friend modi operator+(const modi &a, const modi &b) {return modi(a) += b;}
    friend modi operator-(const modi &a, const modi &b) {return modi(a) -= b;}
    friend modi operator*(const modi &a, const modi &b) {return modi(a) *= b;}
    friend modi operator/(const modi &a, const modi &b) {return modi(a) /= b;}

    friend bool operator==(const modi &a, const modi &b) {return a.v == b.v;}
};
using mint = modi<>;

// S[1] * K^0 + S[2] * K^1 + S[3] * K^2
struct String {
    int N,K; 
    string S;
    vector<mint> hash, pow_hash, inv_hash;

    String(const string &s) : N(sz(s)), K(2377), S(s), hash(N+1), pow_hash(N+1), inv_hash(N+1) {
        pow_hash[0] = 1;
        for(int i = 0; i < N; i++){
            pow_hash[i+1] = pow_hash[i] * K;
            hash[i+1] = hash[i] + pow_hash[i] * (s[i] - '0' + 1);
        }
        inv_hash[N] = inverse(pow_hash[N]);
        for(int i = N-1; i >= 0; i--)
            inv_hash[i] = inv_hash[i+1] * K;
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,tc; cin >> tc;
    string s,t;

    while(tc--){
        cin >> s >> t;
        n = sz(s);

        String S(s), T(t);

        if(s == t){
            cout << "0\n";
            continue;
        }

        int ans = -1;

        for(int i = 0; i < n-1; i++){
            mint pref = S.hash[i+1];
            mint suff = (S.hash[n] - S.hash[i+1]) * S.inv_hash[i+1];

            if(suff + pref * S.pow_hash[n-i-1] == T.hash[n]){
                ans = i+1;
                break;
            }
        }

        cout << ans << endl;
    }
    
    return 0;
}
