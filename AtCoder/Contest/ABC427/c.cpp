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
    vector<int> color;

    Graph(int n) : N(n), adj(N), color(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int solve() {
        int ans = INF;

        for(int p = 0; p < (1 << N); p++){
            for(int j = 0; j < N; j++)
                color[j] = ((p >> j) & 1);

            int sum = 0;

            for(int u = 0; u < N; u++)
                for(int &v : adj[u])
                    if(color[u] == color[v])
                        sum++;

            ans = min(ans, sum/2);
        }

        return ans;
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // 10! >= 3 * 10^6
    int n, m; cin >> n >> m;
    Graph graph(n);

    for(int i = 0, u,v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }

    cout << graph.solve() << endl;
    
    return 0;
}
