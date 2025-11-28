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

struct SegTree {
    int N;
    vector<int> tree;

    SegTree(int n) : N(n), tree(4 * N) {}

    #define lc(x) (x << 1)
    #define rc(x) (x << 1) | 1
    
    void update(int j, int v) {
        modify(1, 0, N - 1, j, v);
    }

    void modify(int x, int l, int r, int j, int v) {
        if(l == r) {
            tree[x] = v;
            return;
        }
        int m = (l + r) >> 1;
        modify(lc(x), l, m, j, v);
        modify(rc(x), m + 1, r, j, v);
        tree[x] = max(tree[lc(x)], tree[rc(x)]);
    }

    int calc(int l, int r) {
        return process(1, 0, N - 1, l, r);
    }

    int process(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) return 0;
        if(ql <= l && r <= qr) return tree[x];
        int m = (l + r) >> 1;
        return max(process(lc(x), l, m, ql, qr), process(rc(x), m + 1, r, ql, qr));
    }
};

struct Tree {
    int N, K;
    vector<vector<int>> adj, par, adj_cen;
    vector<int> sub, vis, dep, pos, par_cen;

    Tree(int n) : N(n), K(log2(N) + 1), adj(N), par(N, vector<int>(K, -1)),
    sub(N), vis(N, 0), dep(N, 0), pos(N), adj_cen(N), par_cen(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void solve() {
        dfs_lca(0);
        dfs_cen(0, -1);

        for(int d = 1; d < K; d++)  
            for(int u = 0; u < N; u++)
                if(par[u][d - 1] != -1)
                    par[u][d] = par[par[u][d - 1]][d - 1];
    }

    void dfs_lca(int u) {
        for(int &v : adj[u]){
            if(v == par[u][0]) continue;
            par[v][0] = u, dep[v] = dep[u] + 1;
            dfs_lca(v);
        }
    }

    int dfs_sub(int u, int p) {
        sub[u] = 1;
        for(int &v : adj[u])
            if(v != p)  
                sub[u] += dfs_sub(v, u);
        return sub[u];
    }

    int cen(int u, int p, int n) {
        for(int &v : adj[u])
            if(v != p && !vis[v] && sub[v] > n / 2)
                return cen(v, u, n);
        return u;
    }

    int dfs_cen(int u, int p) {
        int c = cen(u, -1, dfs_sub(u, -1));
        vis[c] = 1, par_cen[c] = p;

        for(int &v : adj[c])
            if(!vis[v])
                adj_cen[c].pb(dfs_cen(v, c));

        return c;
    }

    int lca(int u, int v) {
        if(dep[u] < dep[v]) swap(u, v);
        int g = dep[u] - dep[v];
        for(int d = 0; d < K; d++) if((g >> d) & 1) u = par[u][d];
        if(u == v) return u;
        for(int d = K - 1; d >= 0; d--) if(par[u][d] != par[v][d]) u = par[u][d], v = par[v][d];
        return par[u][0];
    }

    int distance(int u, int v) {return dep[u] + dep[v] - 2 * dep[lca(u, v)];}

    
};  

int main() {

    FastIO();
    
    
    return 0;
}

