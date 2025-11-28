#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

template <typename T>
struct Fenwick {
    int N;
    vector<T> bit;
    
    Fenwick(int n = 0) : N(n), bit(N + 1, 0) {}

    void update(int i, int v) {
        for(i++; i <= N; i += i & -i) 
            bit[i] += v;
    }
 
    T calc(int i) {
        T sum = 0;
        for(i++; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }
 
    T calc(int l, int r) {
        return calc(r) - calc(l - 1);
    }
};

// For Subtree Queries
template <typename T>
struct FT {
    int N, root;
    vector<vector<int>> adj;
    vector<int> tour, in, out, val;
    vector<int> sub, depth, parent;
    Fenwick<T> fenwick;

    FT(int n) : N(n), in(N), out(N), val(N), adj(N),
                depth(N), parent(N), sub(N, 1), fenwick(N) {}

    void build(int rt = 0) {
        root = rt;  
        depth[root] = 0;
        parent[root] = -1;
        dfs(root);
        
        for(int i = 0; i < N; i++)
            fenwick.update(i, val[tour[i]]);
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int dfs(int u) {
        in[u] = sz(tour);
        tour.pb(u);

        for(const int &v : adj[u]){
            if(v == parent[u]) continue;
            parent[v] = u, depth[v] = depth[u] + 1;
            sub[u] += dfs(v);
        }

        out[u] = sz(tour) - 1;
        return sub[u];
    }

    void update(int u, int x) {
        fenwick.update(in[u], -val[u]);
        val[u] = x;
        fenwick.update(in[u], val[u]);
    }

    T calc(int u) {
        return fenwick.calc(in[u], out[u]);
    }
};

// For Path Queries
template <typename T>
struct FT {
    int N, root, diameter;
    vector<vector<int>> adj;
    vector<int> tour, in, out, val;
    vector<int> sub, depth, parent;
    Fenwick<T> fenwick;

    FT(int n) : N(n), in(N), out(N), val(N), adj(N), depth(N),
                parent(N), sub(N, 1), fenwick(2 * N) {}

    void build(int rt = 0) {
        root = rt;  
        depth[root] = 0;
        parent[root] = -1;
        dfs_sub(root);

        for(int u = 0; u < N; u++){
            fenwick.update(in[u], val[u]);
            fenwick.update(out[u], -val[u]);
        }
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int dfs_sub(int u) {
        in[u] = sz(tour);
        tour.pb(u);

        for(const int &v : adj[u]){
            if(v == parent[u]) continue;
            parent[v] = u, depth[v] = depth[u] + 1;
            sub[u] += dfs_sub(v);
        }

        out[u] = sz(tour);
        tour.pb(u);
        return sub[u];
    }

    bool is_anc(int u, int v) {
        return in[u] < in[v] && out[u] > out[v];
    }

    void update(int u, int x) {
        fenwick.update(in[u], -val[u]);
        fenwick.update(out[u], val[u]);
        val[u] = x;
        fenwick.update(in[u], val[u]);
        fenwick.update(out[u], -val[u]);
    }

    T calc(int u) {
        return fenwick.calc(in[u]);
    }
};

int main(){
 
    FastIO();
    int n; cin >> n;
    FT<int> tree(n);

    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
