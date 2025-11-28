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
const ll INFL = 4e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct SCC {
    int N, M;
    vector<vector<int>> adj, rev_adj, graph;
    vector<int> parent, order, cnt;
    vector<bool> vis;

    SCC(int n) : N(n), M(0), adj(N), rev_adj(N), parent(N), vis(N, 0), cnt(N, 0) {
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

struct Graph {
    int N, K, P; 
    vector<ll> pos;
    SCC scc;

    Graph(int n) : N(n), K(9 * N), P(4 * N), pos(N), scc(9 * N) {
        build1(0, 0, N - 1);
        build2(0, 0, N - 1);
    }

    void add_edge(int u, int v) {
        scc.add_edge(u, v);
    }

    int build1(int x, int l, int r) {
        if(l == r)
            return pos[l] = x;

        int m = (l + r) >> 1;

        add_edge(x, build1((x << 1) + 1, l,     m));
        add_edge(x, build1((x << 1) + 2, m + 1, r));

        return x;
    }

    int build2(int x, int l, int r) {
        if(l == r)
            return pos[l];

        int m = (l + r) >> 1;

        add_edge(build2((x << 1) + 1, l,     m), x + P);
        add_edge(build2((x << 1) + 2, m + 1, r), x + P);

        return x + P;
    }

    // if to == 1, add edge from u to index [l, r]
    // if to == 0, add edge from index [l, r] to u
    // if u is original node, u = pos[u]
    void add_edge(int u, int l, int r, bool to) {
        modify(0, 0, N - 1, u, l, r, to);
    }

    void modify(int x, int l, int r, int u, int ql, int qr, bool to) {
        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            if(to) add_edge(u, x);
            else   add_edge(x + (l == r ? 0 : P), u);
            return;
        }

        int m = (l + r) >> 1;

        modify((x << 1) + 1, l,     m, u, ql, qr, to);
        modify((x << 1) + 2, m + 1, r, u, ql, qr, to);
    }

    // add edge from [a, b] to [c, d]
    void add_edge2(int a, int b, int c, int d, int w) {
        add_edge(K, c, d, 1);
        add_edge(K++, a, b, 0);
    }

    ll solve() {
        scc.build();
    }
};

int main(){
 
    FastIO();

    
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
