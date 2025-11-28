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

struct Tree {
    int N;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> dp;
    vector<int> val, c, vis;
    // dp[u][k] = maximum sum of coin if we have k silver coins

    Tree(int n) : N(n), val(N), adj(N), dp(N, vector<int>(N + 1, -INF)), c(N, 0), vis(N, 0) {}

    void add_edge(int u, int v, int w) {
        adj[v].pb({u, w});
    }

    int solve(int s, int f) {
        dp[s][c[s]] = val[s]; 
        vis[s] = 1;
        dfs(f);
        return *max_element(all(dp[f]));
    }

    void dfs(int u) {
        if(vis[u]) return;
        vis[u] = 1;
        
        for(auto &[v, w] : adj[u]){
            dfs(v);

            for(int j = 0; j <= N; j++){
                int k = j - w;
                if(k < 0) continue;
                k += c[u];
                if(0 <= k && k <= N && dp[v][j] != -INF)
                    dp[u][k] = max(dp[u][k], dp[v][j] + val[u]);
            }
        }
    }
};

int main() {

    FastIO();
    int n,m,s,f; cin >> n >> s >> f;
    s--, f--;

    Tree tree(n);

    for(int &a : tree.val) cin >> a;

    cin >> m;
    for(int i = 0, u,v,w; i < m; i++){
        cin >> u >> v >> w, u--, v--;
        tree.add_edge(u, v, w);
    }

    cin >> m;
    for(int i = 0, u; i < m; i++){
        cin >> u, u--;
        tree.c[u] = 1;
    }

    int ans = tree.solve(s, f);
    cout << (ans == -INF ? -1 : ans) << endl;
    
    return 0;
}

