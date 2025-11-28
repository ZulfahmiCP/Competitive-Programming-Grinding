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
    int N, S[2];
    vector<vector<pair<int, int>>> adj;
    vector<int> vis, group, dist[2];

    Tree(int n, int s1, int s2) : N(n), adj(N), vis(N), group(N, 0) {
        S[0] = s1, S[1] = s2;
    }

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    vector<int> groups(int x) {
        vector<int> g;
        for(int u = 0; u < N; u++)
            if(group[u] == x)
                g.pb(u);
        return g;
    }

    ll solve() {
        dfs_add(S[0], -1, 1, S[1]);
        dfs_add(S[1], -1, -1, S[0]);
        deb(group);
        dfs_dist(S[0], -1, 0);
        dfs_dist(S[1], -1, 1);

        ll ans = 0;

        // Case 1 (u, v) sebelah kiri S1
        vector<int> nodes = groups(1);
        int m = sz(nodes);
        sort(all(nodes), [&](int a, int b) {
            return dist[1][a] < dist[1][b];
        });
        for(int i = 0; i < m; i++)
            ans += dist[1][nodes[i]] * (m - i - 1);

        deb(1, ans);

        // Case 2 (u, v) sebelah kanan S2
        vector<int> nodes = groups(-1);
        int m = sz(nodes);
        sort(all(nodes), [&](int a, int b) {
            return dist[0][a] < dist[0][b];
        });
        for(int i = 0; i < m; i++)
            ans += dist[0][nodes[i]] * (m - i - 1);

        deb(2, ans);

        // Case 3 (u, v) tengah S1 dan S2
        group[S[0]] = group[S[1]] = 0;
        vector<int> nodes = groups(0);
        int m = sz(nodes);
        sort(all(nodes), [&](int a, int b) {
            return dist[0][a] < dist[0][b];
        });
        for(int i = 0; i < m; i++)
            ans += dist[0][nodes[i]] * (m - i - 1);

        return ans;
    }



    void dfs_add(int u, int p, int add, int avoid){
        group[u] += add;
        for(auto &[v, w] : adj[u]){
            if(v == p || v == avoid) continue;
            dfs_add(v, u, add, avoid);
        }
    }

    void dfs_dist(int u, int p, int s) {
        for(auto &[v, w] : adj[u]){
            dist[s][v] = dist[s][u] + w;
            dfs_dist(v, u, s);
        }
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    
    return 0;
}
