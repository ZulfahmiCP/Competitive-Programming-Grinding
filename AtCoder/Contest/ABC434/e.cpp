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
    struct node {
        pair<int, int> w = {INF, INF};
        int u;
        
        bool operator<(const node &oth) const {
            return w < oth.w;
        }
    };
    int N, M;
    vector<vector<int>> adj;
    vector<pair<int, int>> val;
    string S;

    Graph(int n, int m) : N(n), M(m), adj(N), val(N, {INF, INF}) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    bool update(int u, int v) {
        if(v <= val[u].fi){
            val[u].se = val[u].fi;
            val[u].fi = v;
            return 1;
        } else if(v < val[u].se) {
            val[u].se = v;
            return 1;
        }
        return 0;
    }

    void solve() {
        for(int u = 0; u < N; u++){
            if(S[u] != 'S') continue;
            val[u] = {0, INF};
            for(int &v : adj[u])
                if(S[v] == 'S')
                    val[u] = {0, 1};
        }

        priority_queue<node> pq;

        for(int u = 0; u < N; u++){
            if(S[u] != 'D') continue;
            bool ok = 0;

            for(int &v : adj[u]){
                if(S[v] == 'S'){
                    update(u, val[v].fi+1);
                    update(u, val[v].se+1);
                    ok = 1;
                }
            }

            if(ok) pq.push({val[u], u});
        }

        while(!pq.empty()){
            auto [w, u] = pq.top();
            pq.pop();

            if(val[u] < w) continue;

            for(int &v : adj[u]){
                if(S[v] == 'S') continue;
                auto ori = val[v];
                update(v, w.fi+1);
                update(v, w.se+1);

                if(val[v] != ori)
                    pq.push({val[v], v});
            }
        }
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m; cin >> n >> m;
    Graph graph(n, m);

    for(int i = 0, u,v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }

    cin >> graph.S;

    graph.solve();

    for(int u = 0; u < n; u++)
        if(graph.S[u] == 'D'){
            cout << graph.val[u].fi + graph.val[u].se << endl;
            assert(graph.val[u].se != INF);
        }
    
    return 0;
}
