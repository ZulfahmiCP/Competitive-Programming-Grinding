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

struct SCC {
    int N, M;
    vector<vector<int>> adj, rev_adj, graph;
    vector<int> parent, order;
    vector<bool> vis;

    SCC(int n) : N(n), M(0), adj(N), rev_adj(N), parent(N), vis(N, 0) {
        iota(all(parent), 0);
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        rev_adj[v].pb(u);
    }

    void build() {
        for(int u = 0; u < N; u++)
            if(!vis[u]) dfs(u);
        
        fill(all(vis), 0);
        reverse(all(order));

        for(const int &u : order){
            if(vis[u]) continue;
            explore(u);
            M++;
        }
    }

    void dfs(int u) {
        vis[u] = 1;
        for(int &v : adj[u])
            if(!vis[v]) dfs(v);
        order.pb(u);
    }

    void explore(int u) {
        vis[u] = 1;
        for(int v : rev_adj[u]){
            if(vis[v]) continue;
            parent[v] = parent[u];
            explore(v);
        }
    }

    void gen_new_graph() {
        graph.resize(N);

        for(int u = 0; u < N; u++)
            for(const int &v : adj[u])
                if(parent[u] != parent[v])
                    graph[parent[u]].pb(parent[v]);

        for(int u = 0; u < N; u++)
            if(!graph[u].empty())
                make_unique(graph[u]);
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    SCC A(n);

    for(int i = 0, u,v;  i < m; i++){
        cin >> u >> v;
        u--, v--;
        A.add_edge(u, v);
    }

    A.build();
    cout << A.M << '\n';

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
