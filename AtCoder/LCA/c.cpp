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

struct Tree {
    int N;
    vector<vector<int>> adj;
    vector<int> dp, ans;

    Tree(int n) : N(n), adj(N), dp(N, 0), ans(N, 0) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
    }

    int solve() {
        dfs(0, 0);
        return accumulate(all(ans), 0);
    }

    void dfs(int u) {
        if(x > 0 || dp[u] > 1) 
            ans[u] = 1;
        x = max(x, dp[u] + 1);

        for(int &v : adj[u]){
            dfs(v, x - 1);
        }
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q; cin >> n >> q;
    Tree tree(n);

    for(int u = 1, v; u < n; u++){
        cin >> v, v--;
        tree.add_edge(v, u);
    }

    for(int i = 0, u,x; i < q; i++){
        cin >> u >> x, u--;
        tree.dp[u] = max(tree.dp[u], x);
    }

    cout << tree.solve() << endl;
    
    return 0;
}
