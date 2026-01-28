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
 
#ifndef ONLINE_JUDGE
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}
ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<"[ ";for(auto v:c){prd(v);cerr<<' ';}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<"[ ";for(auto v:c){cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cerr<<' ';}cerr<<"]\n";}
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

struct Graph {
    int N, L, S, T;
    vector<vector<pair<int, int>>> adj;
    set<int> ans;

    Graph(int n, int l, int s, int t) : N(n), L(l), S(s), T(t), adj(N) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
    }

    void dfs(int u, int len, int cost) {
        if(len == L){
            if(S <= cost && cost <= T)
                ans.insert(u);
            return;
        }

        for(auto &[v, w] : adj[u])
            dfs(v, len + 1, cost + w);
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,l,s,t; cin >> n >> m >> l >> s >> t;
    Graph graph(n, l, s, t);

    for(int i = 0, u,v,w; i < m; i++){
        cin >> u >> v >> w, u--, v--;
        graph.add_edge(u, v, w);
    }

    graph.dfs(0, 0, 0);

    for(int u : graph.ans) cout << u+1 << ' ';
    
    return 0;
}
