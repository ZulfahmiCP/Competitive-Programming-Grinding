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
const ll INFL = 4e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Dijkstra {
    int N; 
    vector<vector<pair<int, int>>> adj; 
    vector<ll> dist, pos;

    Dijkstra(int n) : N(n), adj(8 * N), dist(8 * N), pos(N) {
        build(0, 0, N - 1);
    }

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
    }

    pair<int, int> build(int x, int l, int r) {
        if(l == r){
            pos[l] = x;
            return {x, x};
        }

        int m = (l + r) >> 1;

        for(auto &[u, v] : {build(2 * x + 1, l, m), build(2 * x + 2, m + 1, r)}){
            add_edge(x, u, 0);
            add_edge(v, x + 4 * N, 0);
        }

        return {x, x + 4 * N};
    }

    void add_edge(int u, int w, int l, int r, bool type) {
        modify(0, 0, N - 1, u, w, l, r, type);
    }

    // type == 0, add edge from index [l, r] to u
    // type == 1, add edge from u to index [l, r]
    void modify(int x, int l, int r, int u, int w, int ql, int qr, int type) {
        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            if(type) add_edge(pos[u], x, w);
            else add_edge(x + (l == r ? 0 : 4 * N), pos[u], w);
            return;
        }

        int m = (l + r) >> 1;

        modify(2 * x + 1, l,     m, u, w, ql, qr, type);
        modify(2 * x + 2, m + 1, r, u, w, ql, qr, type);
    }

    ll solve(int s, int t = 0) {
        fill(all(dist), INFL);
        dist[pos[s]] = 0;

        min_heap<pair<ll, int>> pq;
        pq.push({0, pos[s]});

        while(!pq.empty()){
            const auto [w, u] = pq.top();
            pq.pop();

            if(dist[u] < w)
                continue;

            for(const auto &[v, e] : adj[u]){
                if(dist[u] + e < dist[v]){
                    dist[v] = dist[u] + e;
                    pq.push({dist[v], v});
                } 
            }
        }

        return (dist[t] == INFL ? -1 : dist[t]);
    }

    ll distance(int u) {
        u = pos[u];
        return dist[u] == INFL ? -1 : dist[u];
    }
};

int main(){
 
    FastIO();
    int n, q, s; cin >> n >> q >> s, s--;
    Dijkstra graph(n);

    for(int i = 0, t, u, v, w, l, r; i < q; i++){
        cin >> t;

        if(t == 1){
            cin >> u >> v >> w;
            u--, v--;
            graph.add_edge(graph.pos[u], graph.pos[v], w);
        } else {
            cin >> u >> l >> r >> w;
            u--, l--, r--;
            graph.add_edge(u, w, l, r, t == 2);
        }
    }

    graph.solve(s);

    for(int u = 0; u < n; u++)
        cout << graph.distance(u) << ' ';

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
