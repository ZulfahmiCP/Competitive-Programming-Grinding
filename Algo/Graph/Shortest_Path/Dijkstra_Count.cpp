#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Dijkstra {
    int N; 
    vector<vector<pair<int, int>>> adj; 
    vector<ll> dist, cnt;

    Dijkstra(int n) : N(n), adj(N), dist(N), cnt(N) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    ll solve(int s, int t = 0) {
        fill(all(dist), INFL);
        fill(all(cnt), 0);
        dist[s] = 0, cnt[s] = 1;

        min_heap<pair<ll, int>> pq;
        pq.push({0, s});

        while(!pq.empty()){
            const auto [w, u] = pq.top();
            pq.pop();

            if(dist[u] < w)
                continue;

            for(const auto &[v, e] : adj[u]){
                if(dist[u] + e < dist[v]){
                    dist[v] = dist[u] + e;
                    pq.push({dist[v], v});
                    cnt[v] = cnt[u];
                } else if(dist[u] + e == dist[v]) 
                    cnt[v] += cnt[u];
            }
        }

        return (dist[t] == INFL ? -1 : dist[t]);
    }

    vector<int> kth_path(int s, int t, int k) {
        vector<priority_queue<ll>> best(N);
        min_heap<pair<ll, int>> pq;
        pq.push({0, s});
        best[s].push(0);

        while(!pq.empty()){
            const auto [w, u] = pq.top();
            pq.pop();

            if(best[u].top() < w)
                continue;

            for(const auto &[v, e] : adj[u]){
                if(sz(best[v]) < k){
                    best[v].push(w + e);
                    pq.push({w + e, v});
                } else if(w + e < best[v].top()) {
                    best[v].pop();
                    best[v].push(w + e);
                    pq.push({w + e, v});
                }
            }
        }

        vector<int> path;
        while(!best[t].empty()){
            path.pb(best[t].top());
            best[t].pop();
        }

        reverse(all(path));
        return path;
    }
};

int main(){
 
    FastIO();
    int n,m,k; cin >> n >> m >> k;
    vector path(n, vector<ll>(n, INFL));
    Dijkstra graph(n);

    for(int i = 0, u, v, w; i < m; i++){
        cin >> u >> v >> w, u--, v--;
        graph.add_edge(u, v, w);
    }

    for(int u = 0; u < n; u++){
        graph.solve(u);

        for(int v = 0; v < n; v++)
            path[u][v] = min(path[u][v], graph.dist[v]);
    }

    vector<ll> distance;
    for(int u = 0; u < n; u++){
        for(int v = 0; v < n; v++){
            if(u == v) continue;
            distance.pb(path[u][v]);
            path[v][u] = INFL;
        }
    }

    sort(all(distance));
    distance.resize(k);
    debug(distance);

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
