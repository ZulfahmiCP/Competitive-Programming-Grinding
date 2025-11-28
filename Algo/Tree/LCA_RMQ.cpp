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

struct RMQ {
    int N, K;
    vector<int> arr;
    vector<vector<int>> tab;

    void build(vector<int> &val, vector<int> &cmp) {
        N = sz(val), K = high(N) + 1, arr = cmp;
        tab.resize(K);
        for(int i = 0; i < K; i++) tab[i].resize(N - (1 << i) + 1);
        for(int i = 0; i < N; i++) tab[0][i] = val[i];
        for(int i = 1, a, b; i < K; i++){
            for(int j = 0; j + (1 << i) <= N; j++)
                tab[i][j] = best(tab[i - 1][j], 
                                    tab[i - 1][j + (1 << (i - 1))]);
        }
    }

    int best(int a, int b) {return arr[a] < arr[b] ? a : b;}

    int val(int l, int r) {
        int k = high(r - l + 1);
        return best(tab[k][l], tab[k][r - (1 << k) + 1]);
    }

    int high(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
};

struct LCA {
    int N;
    vector<vector<int>> adj;
    vector<int> in, out, tour, euler, dep, sub, occ;
    RMQ rmq;

    LCA(int n) : N(n), adj(N), in(N), out(N), occ(N),
                    dep(N), sub(N, 1) {}

    void build() {
        dep[0] = 0;
        dfs(0);
        rmq.build(euler, occ);
    }

    int dfs(int u) {
        occ[u] = sz(euler), in[u] = sz(tour);
        euler.pb(u); tour.pb(u);

        for(const int &v : adj[u]) {
            dep[v] = dep[u] + 1, sub[u] += dfs(v);
            euler.pb(u);
        }

        out[u] = sz(tour);
        return sub[u];
    }

    int lca(int u, int v) { u = occ[u], v = occ[v]; if(u > v) swap(u, v); return rmq.val(u, v); }
    int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
    int is_anc(int u, int v) { return in[u] <= in[v] && in[v] < out[u]; }
    bool on_path(int x, int u, int v) { return (is_anc(x,u) || is_anc(x,v)) && is_anc(lca(u,v),x); }
    int degree(int u) { return sz(adj[u]) + (u != 0); }
};

int main() {

    FastIO();
    
    
    return 0;
}

