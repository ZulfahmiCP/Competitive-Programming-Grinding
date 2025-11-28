#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second  
#define ll long long 
#define pb push_back
#define ppb pop_back
#define ld long double 
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define newl cerr << '\n'
#define sz(x) (int)x.size()

#define ttm template 
#define ttp typename 

void FastIO(){ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

ttm<ttp T> void prd(T x){cerr << x;}
ttm<ttp T, ttp U> void prd(pair<T, U> x){cerr<<"("; prd(x.fi); cerr<<", "; prd(x.se); cerr << ")";}
ttm<ttp T, ttp... Args> void prd(T x, Args... arg){prd(x); cerr<<", "; prd(arg...);}
ttm<ttp... Args> void debug(Args... arg){cerr<<"["; prd(arg...); cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr << "["; bool cm=0; for(auto v : c){if(cm); cerr<<", "; prd(v); cm=0;} cerr << "]\n";}

struct SCC {
    int N,M; 
    vector<vector<int>> adj, rev_adj, graph;
    vector<int> val, par, ord, B; 
    vector<bool> vis;

    SCC(int n) : N(n), M(0), adj(N), rev_adj(N), par(N), vis(N, 0), val(N) {
        iota(all(par), 0);
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        rev_adj[v].pb(u);
    }

    void build() {
        for(int u = 0; u < N; u++)
            if(!vis[u]) dfs(u);

        fill(all(vis), 0);
        reverse(all(ord));

        for(const int &u : ord){
            if(vis[u]) continue;
            explore(u); M++;
        }
    }

    void dfs(int u) {
        vis[u] = 1;
        for(int &v : adj[u])
            if(!vis[v]) dfs(v);
        ord.pb(u);
    }

    void explore(int u) {
        vis[u] = 1;
        for(int &v : rev_adj[u]){
            if(vis[v]) continue;
            par[v] = par[u];
            val[par[u]] = min(val[par[u]], val[v]);
            explore(v);
        }
    }

    void gen_new_graph() {
        graph.resize(N);

        for(int u = 0; u < N; u++)
            for(const int &v : adj[u]) 
                if(par[u] != par[v])
                    graph[par[u]].pb(par[v]);

        for(int u = 0; u < N; u++)
            if(!graph[u].empty())
                make_unique(graph[u]); 
    }

    ll solve() {
        ord.clear();
        vector<int> deg(N, 0), X;

        // debug(B); debug(M, sz(B)); 
        // debug(val); debug(par);

        for(int u = 0; u < N; u++) if(u == par[u])
            for(int &v : graph[u])
                deg[v]++;

        // debug(deg);

        for(int u = 0; u < N; u++)  
            if(!deg[u] && u == par[u]) 
                X.pb(val[u]);

        sort(all(B));
        while(sz(B) > sz(X)) B.ppb();

        if(sz(B) < sz(X)) return -1;

        sort(all(B));
        sort(All(X));

        // debug(X); debug(B);

        ll ans = 0;
        for(int i = 0; i < sz(X); i++)
            ans += 1LL * X[i] * B[i];
        return ans;
    }
};

int main() {

    FastIO();
    int n,m,p; cin >> n >> m >> p;
    vector<int> A(n), B(p);

    SCC graph(n);

    for(int &a : A) cin >> a;
    for(int &a : B) cin >> a;

    graph.val = A, graph.B = B;

    for(int i = 0, u,v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }

    graph.build();
    graph.gen_new_graph();

    cout << graph.solve() << '\n';

    return 0;
}