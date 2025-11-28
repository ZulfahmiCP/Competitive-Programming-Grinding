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

struct Tree {
    int N, K;
    vector<vector<int>> adj, par;
    vector<int> dep;

    Tree(int n) : N(n), K(log2(n) + 1), adj(N), par(N, vector<int>(K, -1)), dep(N, 0) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build() {
        dfs(0);

        for(int d = 1; d < K; d++)
            for(int u = 0; u < N; u++)
                if(par[u][d - 1] != -1)
                    par[u][d] = par[par[u][d - 1]][d - 1];
    }

    void dfs(int u) {
        for(int &v : adj[u]){
            if(v == par[u][0]) continue;
            par[v][0] = u;
            dep[v] = dep[u] + 1;
            dfs(v);
        }
    }

    int lca(int u, int v) {
        if(dep[u] < dep[v]) swap(u, v);

        int g = dep[u] - dep[v];

        for(int d = 0; d < K; d++)
            if((g >> d) & 1)
                u = par[u][d];

        if(u == v) return u;

        for(int d = K - 1; d >= 0; d--)
            if(par[u][d] != par[v][d])
                u = par[u][d], v = par[v][d];

        return par[u][0];
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, q; cin >> n >> q;
    Tree tree(n);

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.build();

    for(int i = 0, u,v; i < q; i++){
        cin >> u >> v, u--, v--;
        cout << (tree.dist(u, v) & 1 ? "Road" : "Town") << endl;
    }
    
    return 0;
}
