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

struct ArticPoint {
    int N, timer; 
    vector<vector<int>> adj;
    vector<int> tin, low, art_point;  
    vector<bool> art;

    ArticPoint(int n) : N(n), timer(0), adj(N), art(N, 0), 
                        tin(N, -1), low(N, -1) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build() {
        for(int u = 0; u < N; u++){
            if(!tin[u]) dfs(u, -1);
            if(art[u]) art_point.pb(u);
        }
    }

    void dfs(int u, int p) {
        int child = 0;
        tin[u] = low[u] = timer++;

        for(const int &v : adj[u]){
            if(v == p) continue;
            if(!tin[v]){
                child++;
                dfs(v, u);
                
                low[u] = min(low[u], low[v]);
                if(low[v] >= tin[u] && p != -1)
                    art[u] = 1;
            } else if (v != p) 
                low[u] = min(low[u], tin[v]);
        }

        if(p == -1 && child > 1)
            art[u] = 1;
    }
};

int main() {
    
    FastIO();
    int n, m; cin >> n >> m;
    ArticPoint graph(n);

    for(int i = 0, u, v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }

    graph.build();
    cout << sz(graph.art_point) << '\n';
    for(int &v : graph.art_point)
        cout << v + 1 << ' ';

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
