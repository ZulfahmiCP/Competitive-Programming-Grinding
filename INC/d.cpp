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

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);

    for(int i = 0, u,v,w; i < m; i++){
        cin >> u >> v, u--, v--;
        cin >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    auto dijkstra = [&](int s) -> vector<ll> {
        vector<ll> dist(n, INFL);
        dist[s] = 0;

        min_heap<pair<ll, int>> pq;
        pq.push({0, s});

        while(!pq.empty()){
            const auto [w, u] = pq.top(); 
            pq.pop();

            if(dist[u] < w) continue;

            for(const auto &[v, e] : adj[u]){
                if(dist[u] + e < dist[v]){
                    dist[v] = dist[u] + e;
                    pq.push({dist[v], v});
                } 
            }
        }

        return dist;
    };

    auto dista0 = dijkstra(0);
    auto dista1 = dijkstra(1);
    auto dista2 = dijkstra(2);

    for(int u = 0; u < n; u++)
        for(auto &[v, w] : adj[u])
            w = ceil(w / 2.0);

    auto distb1 = dijkstra(1);

    ll ans = INFL;

    for(int u = 0; u < n; u++){
        // 1 -> u -> 2
        // 2 -> u -> 3

        ans = min(ans, dista0[u] + dista1[u] + distb1[u] + dista2[u]);
    }

    cout << ans << endl;
    
    return 0;
}
