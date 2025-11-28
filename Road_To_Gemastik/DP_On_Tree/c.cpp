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

struct Graph {
    int N;
    vector<vector<int>> adj;
    vector<int> dp;

    Graph(int n) : N(n), adj(N), dp(N, -1) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
    }

    vector<int> solve() {
        dp[N - 1] = 1;
        dfs(0);

        if(!dp[0]) return {};

        vector<int> ans;

        int u = 0;
        while(true){
            ans.pb(u+1);
            if(u == N - 1) break;
            for(int &v : adj[u]){
                if(dp[v] + 1 == dp[u]){
                    u = v;
                    break;
                }
            }
        }

        return ans;
    }

    void dfs(int u) {
        if(dp[u] != -1) return;

        dp[u] = 0;

        for(int &v : adj[u]){
            dfs(v);
            if(dp[v])
                dp[u] = max(dp[u], dp[v] + 1);
        }
    }
};

int main() {

    FastIO();
    int n,m; cin >> n >> m;
    Graph graph(n);

    for(int i = 0, u,v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }

    auto ans = graph.solve();

    if(ans.empty()){
        cout << "IMPOSSIBLE\n";
    } else {
        cout << sz(ans) << endl;
        for(int &a : ans) cout << a << ' ';
    }
    
    return 0;
}

