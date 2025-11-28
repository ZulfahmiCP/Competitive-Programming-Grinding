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
    vector<int> in, out, tour, euler, weight;
    vector<int> depth, sub, occ, parent;
	RMQ rmq;
    
    LCA(int n) : N(n), adj(N), in(N), out(N), occ(N),
                 depth(N), sub(N, 1), parent(N), weight(N, 0) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    void build(int rt = 0) {
        root = rt;
        depth[root] = 0;
        parent[root] = -1;
        dfs(root);
		rmq.build(euler, occ);
    }

    int dfs(int u) {
        occ[u] = sz(euler), in[u] = sz(tour);
        euler.pb(u); tour.pb(u);

        for(const auto &[v, w] : adj[u]) {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            weight[v] = weight[u] + w;
            eliminate(adj[v], make_pair(u, w));
            sub[u] += dfs(v);
            euler.pb(u);
        }

        out[u] = sz(tour);
        return sub[u];
    }

    int lca(int u, int v) { u = occ[u], v = occ[v]; if(u > v) swap(u, v); return rmq.val(u, v);}
    int path_weight(int u, int v) { return weight[u] + weight[v] - 2 * weight[lca(u, v)]; }
    int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
    bool on_path(int x, int u, int v) { return (is_anc(x, u) || is_anc(x, v)) && is_anc(lca(u, v), x); }
    bool is_anc(int u, int v) { return in[u] <= in[v] && in[v] < out[u]; }
    int degree(int u) { return sz(adj[u]) + (u != 0); }
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
