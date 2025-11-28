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

// struct BellmanFord {
//     int N;
//     vector<vector<pair<int, int>>> adj; 
//     vector<int> par, cycle;
//     vector<ll> dist; 

//     BellmanFord(int n) : N(n), adj(n), par(N, -1), dist(n, INFL) {}

//     void add_edge(int u, int v, int w) {
//         adj[u].pb({v, w});
//     }

//     bool solve(int s) {
//         dist[s] = 0;

//         int x;
//         for(int i = 1; i < N; i++){ x = -1;
//             for(int u = 0; u < N; u++) if(dist[u] != INFL)
//                 for(const auto &[v, w] : adj[u])  
//                     if(dist[u] + w < dist[v])
//                         dist[v] = dist[u] + w, par[v] = u;
//         }

//         if(x == -1) return 1;

//         for(int i = 0; i < N; i++) x = par[x];

//         for(int v = x;;v = par[v]){
//             cycle.pb(v);
//             if(v == x && sz(cycle) > 1)
//                 break;
//         }

//         reverse(all(cycle));

//         return 0;
//     }
// };


struct Graph {
    int N;
    vector<vector<pair<int, int>>> adj;
    vector<ll> dist;
    vector<int> par;

    Graph(int n) : N(2 * n), adj(N), par(N, -1), dist(N, INFL) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
    }

    ll solve(int s, int t) {
        dist[2 * s] = dist[2 * s + 1] = 0;

        int x = -1;
        for(int i = 1; i < N; i++){ 
            x = -1;

            for(int u = 0; u < N; u++) 
                for(auto &[v, w] : adj[u])  
                    if(dist[u] + w < dist[v])
                        dist[v] = dist[u] + w, par[v] = u, x = v;
        }

        if(x != -1) return INFL;
        return min(dist[2 * t], dist[2 * t + 1]);
    }
};

int main() {

    FastIO();
    int T,n,m; cin >> T;
    ll ans;

    for(int tc = 1; tc <= T; tc++){
        cin >> n >> m;
        Graph graph(n);

        for(int i = 0, u,v,x,y; i < m; i++){
            cin >> u >> v, u--, v--;
            cin >> x >> y;

            graph.add_edge(2 * u, 2 * v + 1, x);
            graph.add_edge(2 * v, 2 * u + 1, x);
            graph.add_edge(2 * u + 1, 2 * v, y);
            graph.add_edge(2 * v + 1, 2 * u, y);
        }

        cout << "Case #" << tc << ": ";

        ans = graph.solve(0, n - 1);
        if(ans != INFL) cout << ans << endl;
        else cout << "abyss\n";
    }
    
    return 0;
}

