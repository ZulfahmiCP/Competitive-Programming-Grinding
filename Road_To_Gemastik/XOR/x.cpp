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

struct FT {
    int N;
    vector<vector<int>> adj;
    vector<int> tour, in, out, val;
    vector<int> sub, dep, par;
    Fenwick<ll> fen;

    FT(int n) : N(n), in(N), out(N), val(N), adj(N),
                    dep(N), par(N), sub(N, 1), fen(N) {}

    void build(int root = 0) {
        dep[root] = 0, par[root] = -1;
        dfs(root);
        
        // Subtree
        for(int i = 0; i < N; i++)
            fen.update(i, val[tour[i]]);
        // Path
        for(int u = 0; u < N; u++){
            fen.update(in[u], val[u]);
            fen.update(out[u], -val[u]);
        }
    }

    int dfs(int u) {
        in[u] = sz(tour);
        tour.pb(u);

        for(const int &v : adj[u]){
            if(v == par[u]) continue;
            par[v] = u, dep[v] = dep[u] + 1;
            sub[u] += dfs(v);
        }

        out[u] = sz(tour) - 1;
        return sub[u];
    }

    void update(int u, int x) {
        // Subtree
        fen.update(in[u], -val[u]);
        val[u] = x;
        fen.update(in[u], val[u]);
        // Path 
        fen.update(in[u], -val[u]);
        fen.update(out[u], val[u]);
        val[u] = x;
        fen.update(in[u], val[u]);
        fen.update(out[u], -val[u]);
    }

    ll calc(int u) {
        // Subtree
        return fen.calc(in[u], out[u]);
        // Path 
        return fen.calc(in[u]);
    }
};

int main() {

    FastIO();
    
    
    return 0;
}

