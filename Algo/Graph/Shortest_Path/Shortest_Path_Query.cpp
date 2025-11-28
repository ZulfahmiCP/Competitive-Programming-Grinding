#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>

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

struct RMQ {
	int N, K;
	vector<int> A;
	vector<vector<int>> table;

	void build(const vector<int> &vals, const vector<int> &comp) {
		N = vals.size(), K = high(N) + 1, A = comp;
		table.resize(K);

		for(int i = 0; i < K; i++)
			table[i].resize(N - (1 << i) + 1);
		
		for(int i = 0; i < N; i++)
			table[0][i] = vals[i];

		for(int i = 1, a, b; i < K; i++){
            for(int j = 0; j + (1 << i) <= N; j++)
                table[i][j] = best(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
        }
	}

	int best(int a, int b) {
		return A[a] < A[b] ? a : b;
	}

	int val(int l, int r) {
		int k = high(r - l + 1);
        return best(table[k][l], table[k][r - (1 << k) + 1]);
	}

	int high(int x) {
		return x == 0 ? -1 : 31 - __builtin_clz(x);
	}
};

struct LCA {
    int N, root;
    vector<vector<pair<int, int>>> adj;
    vector<int> euler, occ;
    vector<ll> weight;
    vector<bool> vis;
	RMQ rmq;
    
    LCA(int n) : N(n), adj(N), occ(N), vis(N), weight(N) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    void build(int rt, set<pair<int, int>> &bad) {
        root = rt;
        weight[root] = 0;
        dfs(root, -1, bad);
		rmq.build(euler, occ);
    }

    void dfs(int u, int p, set<pair<int, int>> &bad) {
        vis[u] = 1;
        occ[u] = sz(euler);
        euler.pb(u); 

        for(const auto &[v, w] : adj[u]) {
            if(vis[v] || v == p) continue;
            weight[v] = weight[u] + w;
            bad.erase({min(u, v), max(u, v)});
            dfs(v, u, bad);
            euler.pb(u);
        }
    }

    int lca(int u, int v) { u = occ[u], v = occ[v]; if(u > v) swap(u, v); return rmq.val(u, v);}
    ll dist(int u, int v) { return weight[u] + weight[v] - 2 * weight[lca(u, v)]; }
};

struct Dijkstra {
    vector<ll> dist;

    Dijkstra() {}
    Dijkstra(int s, const vector<vector<pair<int, int>>> &adj) {
        dist.resize(sz(adj), INFL);
        dist[s] = 0;

        min_heap<pair<ll, int>> explore;
        explore.push({0, s});

        while(!explore.empty()){
            const auto [w, u] = explore.top();
            explore.pop();

            if(dist[u] < w)
                continue;

            for(const auto &[v, e] : adj[u]){
                if(dist[u] + e < dist[v]){
                    dist[v] = dist[u] + e;
                    explore.push({dist[v], v});
                } 
            }
        }
    }

    ll& operator[](int v) {
        return dist[v];
    }
};

struct SPQ {
    int N, M;
    set<pair<int, int>> bad;
    vector<vector<pair<int, int>>> adj;
    vector<Dijkstra> graph;
    LCA tree;

    SPQ(int n, int m) : N(n), M(m), adj(N), tree(N) {}

    void add_edge(int u, int v, int w) {
        if(u > v) swap(u, v);
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        tree.add_edge(u, v, w);
        bad.insert({u, v});
    }

    void build() {
        tree.build(0, bad);
        for(auto [u, v] : bad)
            graph.pb(Dijkstra(u, adj));
    }

    ll dist(int u, int v) {
        ll d = tree.dist(u, v);
        for(auto &g : graph)
            d = min(d, g[u] + g[v]);
        return d;
    }
};  

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    SPQ graph(n, m);

    for(int i = 0, u, v, w; i < m; i++){
        cin >> u >> v >> w, u--, v--;
        graph.add_edge(u, v, w);
    }

    graph.build();

    int q, u, v; cin >> q;
    while(q--){
        cin >> u >> v, u--, v--;
        cout << graph.dist(u, v) << '\n';
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
