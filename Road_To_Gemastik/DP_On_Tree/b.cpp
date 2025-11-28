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

    friend modi operator+(const modi &a, const modi &b) {return modi(a) += b;}
};
using mint = modi<>;

struct Graph {
    int N;
    vector<vector<int>> adj;
    vector<mint> dp;
    vector<bool> vis;

    Graph(int n) : N(n), adj(N), dp(N, 0), vis(N, 0) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
    }

    int solve() {   
        dp[N - 1] = 1;
        vis[N - 1] = 1;
        return dfs(0).v;
    }

    mint dfs(int u) {
        if(vis[u]) return dp[u];

        vis[u] = 1;

        for(int &v : adj[u])
            dp[u] += dfs(v);

        return dp[u];
    }
};

int main() {

    FastIO();
    int n,m; cin >> n >> m;
    Graph graph(n);

    for(int i = 0, u,v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }

    cout << graph.solve() << endl;
    
    return 0;
}

