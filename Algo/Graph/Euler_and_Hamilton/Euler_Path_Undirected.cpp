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

struct Euler {
    int N, M;
    vector<vector<pair<int, int>>> adj;
    vector<int> path, deg;
    vector<bool> vis;

    Euler(int n, int m) : N(n), M(m), adj(N), deg(N, 0), vis(M) {}

    void add_edge(int u, int v, int i) {
        adj[u].pb({v, i});
        adj[v].pb({u, i});
        deg[u]++;
        deg[v]++;
    }

    bool euler_circuit(int s = 0) {
        path.clear();
        fill(all(vis), 0);
        
        for(int u = 0; u < N; u++)
            if(deg[u] & 1)
                return 0;
            
        dfs(s);

        return sz(path) == M + 1;
    }

    void dfs(int u) {
        for(auto &[v, e] : adj[u]){
            if(vis[e]) return;
            vis[e] = 1;
            dfs(v);
        }

        path.pb(u);
    } 
};

int main(){
 
    FastIO();
    int n, m; cin >> n >> m;
    Euler graph(n, m);

    for(int i = 0, u, v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v, i);
    }

    if(graph.euler_circuit(0)){
        for(int &u : graph.path) 
            cout << u + 1 << ' ';
    } else 
        cout << "IMPOSSIBLE\n";

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
