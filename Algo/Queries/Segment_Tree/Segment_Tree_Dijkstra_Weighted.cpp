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
    int N, K, P; 
    vector<vector<pair<int, int>>> adj; 
    vector<ll> dist, pos;

    Dijkstra(int n) : N(n), K(9 * N), P(4 * N), adj(9 * N), dist(9 * N), pos(N) {
        build1(0, 0, N - 1);
        build2(0, 0, N - 1);
    }

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
    }

    int build1(int x, int l, int r) {
        if(l == r)
            return pos[l] = x;

        int m = (l + r) >> 1;

        add_edge(x, build1((x << 1) + 1, l,     m), 0);
        add_edge(x, build1((x << 1) + 2, m + 1, r), 0);

        return x;
    }

    int build2(int x, int l, int r) {
        if(l == r)
            return pos[l];

        int m = (l + r) >> 1;

        add_edge(build2((x << 1) + 1, l,     m), x + P, 0);
        add_edge(build2((x << 1) + 2, m + 1, r), x + P, 0);

        return x + P;
    }

    // if to == 1, add edge from u to index [l, r]
    // if to == 0, add edge from index [l, r] to u
    // if u is original node, u = pos[u]
    void add_edge(int u, int w, int l, int r, bool to) {
        modify(0, 0, N - 1, u, w, l, r, to);
    }

    void modify(int x, int l, int r, int u, int w, int ql, int qr, bool to) {
        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            if(to) add_edge(u, x, w);
            else   add_edge(x + (l == r ? 0 : P), u, w);
            return;
        }

        int m = (l + r) >> 1;

        modify((x << 1) + 1, l,     m, u, w, ql, qr, to);
        modify((x << 1) + 2, m + 1, r, u, w, ql, qr, to);
    }

    // add edge from [a, b] to [c, d]
    void add_edge2(int a, int b, int c, int d, int w) {
        add_edge(K, 0, c, d, 1);
        add_edge(K++, w, a, b, 0);
    }

    ll solve(int s, int t = 0) {
        fill(all(dist), INFL);
        s = pos[s], t = pos[t];
        dist[s] = 0;

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
    int t,n,m,x,y; cin >> t;
    while(t--){
        cin >> n >> m >> x >> y, x--, y--;
        vector<array<int, 4>> edges(m);
        Map<int, int> who;
        vector<int> nodes;

        nodes.pb(x), nodes.pb(y);

        for(auto &[a, b, c, d] : edges){
            cin >> a >> b >> c >> d;
            a--, b--, c--, d--;
            nodes.pb(a);
            nodes.pb(b);
            nodes.pb(c);
            nodes.pb(d);
        }

        make_unique(nodes);

        n = sz(nodes);
        for(int i = 0; i < n; i++)
            who[nodes[i]] = i;

        Dijkstra graph(n);

        x = who[x], y = who[y];

        for(auto &[a, b, c, d] : edges){
            a = who[a], b = who[b], c = who[c], d = who[d];
            graph.add_edge2(a, b, c, d, 1);
        }

        cout << graph.solve(x, y) << '\n';
    }

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
