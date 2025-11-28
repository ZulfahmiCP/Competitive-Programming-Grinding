#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long 
#define pb push_back
#define ppb pop_back
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'

struct Graph {
    int N;
    vector<int> val;
    vector<vector<int>> adj;
    vector<map<int, int>> dp;

    Graph(int n) : N(n), val(N), adj(N), dp(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int solve() {
        for(int u = 0; u < N; u++){
            for(int &v : adj[u]){
                if(val[v] - val[u] > 0){
                    dfs(u, val[v] - val[u]);
                }
            }
        }

        int ans = 0;

        for(int u = 0; u < N; u++)
            for(auto [e, w] : dp[u])
                ans = max(ans, w);
                
        return ans;
    }

    void dfs(int u, int w) {
        if(dp[u].find(w) != dp[u].end()) return;
        dp[u][w] = 1;

        for(auto &v : adj[u]){
            if(val[v] - val[u] == w){
                dfs(v, w);
                dp[u][w] = max(dp[u][w], dp[v][w] + 1);
            }
        }
    }
};

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n,m; cin >> n >> m;
    Graph graph(n);

    for(int &a : graph.val) cin >> a;

    for(int i = 0, u,v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }

    cout << graph.solve() << endl;

    return 0;
}
