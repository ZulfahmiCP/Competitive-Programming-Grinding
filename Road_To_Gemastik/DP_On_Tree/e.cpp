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


template<const int M = MOD> struct modi {
    int v;

    modi(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}

    modi& operator+=(const modi &b) {v += b.v; if(v >= M) v -= M; return *this;}
    modi& operator*=(const modi &b) {v = (ll)v * b.v % M; return *this;}

    friend modi operator+(const modi &a, const modi &b) {return modi(a) += b;}
    friend modi operator*(const modi &a, const modi &b) {return modi(a) *= b;}
};
using mint = modi<>;

struct Tree {
    int N;
    vector<vector<int>> adj;
    vector<array<mint, 2>> dp;
    // dp[u][0] = banyaknya cara mewarnai subtree di u denga u putih
    // dp[u][1] = banyaknya cara mewarnai subtree di u denga u hitam

    Tree(int n) : N(n), adj(N), dp(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int solve() {
        dfs(0, -1);

        return (dp[0][0] + dp[0][1]).v;
    }

    void dfs(int u, int p) {
        dp[u][0] = dp[u][1] = 1;

        for(int &v : adj[u]){
            if(v == p) continue;
            dfs(v, u);
            dp[u][0] *= (dp[v][0] + dp[v][1]);
            dp[u][1] *= dp[v][0];
        }
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    Tree tree(n);

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    cout << tree.solve() << endl;
    
    return 0;
}

