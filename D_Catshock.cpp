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
    int N;
    vector<vector<int>> adj;
    vector<int> subN, deg, dep, par;
    vector<pair<int, int>> ans;
    queue<int> leaf;
    int cur = 0;

    Graph(int n) : N(n), adj(N), subN(N, 0), deg(N, 0), dep(N, 0), par(N, -1) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
        deg[u]++, deg[v]++;
    }

    void dfs2(int u, int p) {
        subN[u] = 1;
        par[u] = p;

        for(int &v : adj[u]){
            if(v == p) continue;
            dep[v] = dep[u] ^ 1;
            dfs2(v, u);
        }
    }

    bool dfs(int u, int p) {
        par[u] = p;

        if(u == N - 1){
            dfs2(u, p);
            return 1;
        }

        bool ok = 0;

        for(int &v : adj[u]){
            if(v == p) continue;
            dep[v] = dep[u] ^ 1;
            if(dfs(v, u)) ok = 1;
        }

        if(u != 0 && sz(adj[u]) == 1 && !ok)
            leaf.push(u);

        return subN[u] = ok;
    }

    void process_leaves() {
        while(!leaf.empty()){
            int u = leaf.front();
            leaf.pop();

            ans.pb({1, -1});
            cur = !cur;

            if(dep[u] == cur){
                ans.pb({1, -1});
                cur = !cur;
            } 

            ans.pb({2, u});
            
            deg[par[u]]--;
            if(par[u] != 0 && par[u] != N - 1 && deg[par[u]] == 1)
                leaf.push(par[u]);
        }
    }

    void process() {
        dfs(0, -1);

        process_leaves();

        for(int u = 1; u < N - 1; u++)
            if(subN[u] && sz(adj[u]) == 1)
                leaf.push(u);

        process_leaves();

        int u = 0;
        while(u != N - 1){
            ans.pb({1, -1});
            cur = !cur;

            if(dep[u] == cur){
                ans.pb({1, -1});
                cur = !cur;
            }

            ans.pb({2, u});

            int w = -1;

            for(int &v : adj[u])
                if(subN[v] && v != par[u])
                    w = v;

            assert(w != -1);

            u = w;
        }
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t,n; cin >> t;

    while(t--){
        cin >> n;
        Graph graph(n);

        for(int i = 1, u,v; i < n; i++){
            cin >> u >> v, u--, v--;
            graph.add_edge(u, v);
        }

        graph.process();

        cout << sz(graph.ans) << endl;

        for(auto &[op, u] : graph.ans){
            cout << op << ' ';
            if(op == 2) cout << u+1;
            cout << endl;
        }

        cout << endl;
    }
    
    return 0;
}
