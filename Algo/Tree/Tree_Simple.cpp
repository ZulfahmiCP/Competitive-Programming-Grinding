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

struct Tree {
    int N;
    vector<vector<int>> adj;
    vector<int> sub, depth, parent;

    Tree(int n) : N(n), adj(N), sub(N, 1), depth(N), parent(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build(int root = 0) {
        depth[root] = 0;
        parent[root] = -1;
        dfs_sub(root);
    }

    int dfs_sub(int u) {
        for(const int &v : adj[u]){
            if(v == parent[u]) continue;
            parent[v] = u, depth[v] = depth[u] + 1;
            sub[u] += dfs_sub(v);
        }

        return sub[u];
    }

    friend istream& operator>>(istream& is, Tree &tree){
        for(int i = 1, u, v; i < tree.N; i++){
            is >> u >> v, u--, v--;
            tree.add_edge(u, v);
        }

        tree.build();

        return is;
    }
};

struct Treet {
    int N;
    vector<vector<pair<int, int>>> adj;
    vector<int> sub, depth, parent, weight;

    Treet(int n) : N(n), adj(N), depth(N), sub(N, 1), parent(N), weight(N, 0) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    void build(int root = 0) {
        depth[root] = 0;
        parent[root] = -1;
        dfs_sub(root);
    }

    int dfs_sub(int u) {
        for(const auto &[v, w] : adj[u]){
            if(v == parent[u]) continue;
            parent[v] = u, depth[v] = depth[u] + 1;
            sub[u] += dfs_sub(v);
            weight[u] += w + weight[v];
        }

        return sub[u];
    }

    friend istream& operator>>(istream& is, Treet &tree){
        for(int i = 1, u, v, w; i < tree.N; i++){
            is >> u >> v >> w;
            tree.add_edge(--u, --v, w);
        }

        tree.build();

        return is;
    }
};

int main(){
 
    FastIO();
    int t,n; cin >> t;
    while(t--){
        cin >> n;
        Tree tree(n); cin >> tree;

        
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
