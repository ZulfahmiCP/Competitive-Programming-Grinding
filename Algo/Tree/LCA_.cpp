#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'

using namespace std;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& x);
template<typename T, typename... A>void prd(const T& x, A... a);
template<typename... A>void debug(A... a);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);
void fail() {debug("DONE"); exit(0);}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct LCA {
    int N, K, root, timer;
    vector<vector<int>> par, adj; 
    vector<int> dep, sub, in, out, tour;   

    LCA(int n = 0) : N(n), K(log2(N) + 1), par(N, vector<int>(K, -1)),
                     dep(N), sub(N, 1), in(N), out(N), adj(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build(int root = 0) {
        dep[root] = 0, par[root][0] = -1;
        dfs(root);

        for(int d = 1; d < K; d++)
            for(int u = 0; u < N; u++)
                if(par[u][d - 1] != -1)
                    par[u][d] = par[par[u][d - 1]][d - 1];
    }

    int dfs(int u) {
        eliminate(adj[u], par[u][0]);
        in[u] = sz(tour);
        tour.pb(u);

        for(const int &v : adj[u]){
            par[v][0] = u;
            dep[v] = dep[u] + 1;
            sub[u] += dfs(v);
        }

        out[u] = sz(tour);

        return sub[u];
    }

    int lca(int u, int v) {
        if(dep[u] < dep[v]) swap(u, v); 
        if(is_anc(u, v)) return u;

        int goal = dep[u] - dep[v];

        for(int d = 0; d < K; d++) 
            if((goal >> d) & 1)
                u = par[u][d];

        if(u == v) 
            return u;

        for(int d = K - 1; d >= 0; d--) 
            if(par[u][d] != par[v][d])
                u = par[u][d], v = par[v][d];

        return par[u][0]; 
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    int kth_anc(int u, int k) {
        if(k > dep[u])
            return -1;
        
        int goal = dep[u] - k;

        for(int d = 0; d < K; d++)
            if((goal > d) & 1)
                u = par[u][d];
        
        return u;
    }

    int is_anc(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }

    bool on_path(int x, int u, int v) {
        return (is_anc(x, u) || is_anc(x, v)) && is_anc(lca(u, v), x);
    }
};

int main(){
 
    FastIO();


    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
template<typename T, typename... A>void prd(const T& x, A... a){prd(x);cerr<<", ";prd(a...);}
template<typename... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
