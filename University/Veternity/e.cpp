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
#define endl '\n'

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
const ll INFL = 1e18; 

void FastIO();

struct Dijkstra {
    int N; 
    vector<vector<pair<int, int>>> adj; 
    vector<ll> dist, safe;

    Dijkstra(int n) : N(n), adj(N), dist(N), safe(N, INFL) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    ll solve2(int s, int t) {
        fill(all(dist), INFL);
        if (safe[s] <= 0) return -1;
        dist[s] = 0;

        min_heap<pair<ll, int>> pq;
        pq.push({0, s});

        while(!pq.empty()){
            auto [w, u] = pq.top();
            pq.pop();

            if(dist[u] < w) continue;

            for(auto &[v, e] : adj[u]){
                ll x = dist[u] + e;
                if(x < safe[v] && x < dist[v]){
                    dist[v] = x;
                    pq.push({dist[v], v});
                } 
            }
        }

        return (dist[t] == INFL ? -1 : dist[t]);
    }

    void solve(vector<int> &B) {
        min_heap<pair<ll, int>> pq;
        fill(all(dist), INFL);

        for(int sc : B){
            if(safe[sc] > 0){ 
                dist[sc] = 0;
                pq.push({0, sc});
            }
        }

        while(!pq.empty()){
            auto [w, u] = pq.top(); 
            pq.pop();

            if(dist[u] < w) continue;

            for(auto &[v, e] : adj[u]){
                ll x = dist[u] + e;
                if(x < dist[v]){
                    dist[v] = x;
                    pq.push({dist[v], v});
                }
            }
        }

        for(int u = 0; u < N; u++)
            safe[u] = min(safe[u], dist[u]);
    }
};

int main(){

    FastIO();
    int n,t,m,k,q,s,x;
    cin >> n >> t >> m >> k >> q >> s >> x;
    s--, x--; 

    vector<pair<ll, ll>> A(t), C(q);
    vector<array<int, 3>> edges(m);
    vector<int> B(k);
    Dijkstra graph(n);

    for(auto &[a, b] : A) cin >> a >> b, a--;
    for(auto &[u, v, w] : edges) cin >> u >> v >> w, u--, v--;
    for(int &a : B) cin >> a, a--;
    for(auto &[a, b] : C){
        cin >> a >> b, b--;
        graph.safe[b] = min(graph.safe[b], a);
    }
    
    for(auto &[u, v, w] : edges) 
        graph.add_edge(u, v, w);

    graph.solve(B);
    
    Dijkstra graph2(n);
    graph2.safe = graph.safe; 
    
    for(auto &[u, v, w] : edges) 
        graph2.add_edge(u, v, w);
    
    for(int i = 0; i < t; i++){
        for(int j = i + 1; j < t; j++){
            ll w = abs(A[i].se - A[j].se);
            graph2.add_edge(A[i].fi, A[j].fi, w);
        }
    }
    
    cout << graph2.solve2(s, x) << '\n';

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