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

struct Graph {
    int N, max_depth = 30;
    vector<int> pos, deg, cycle, cycle_pos, cycle_length;
    vector<array<int, 30>> parent;

    Graph(int n) : N(n), parent(N), pos(N, -1), deg(N, 0), cycle(N, 1), cycle_pos(N, -1), cycle_length(N, 0) {}

    void add_edge(int u, int v) {
        parent[u][0] = v;
        deg[v]++;
    }

    void build() {
        for(int d = 1; d < max_depth; d++)
            for(int u = 0; u < N; u++)
                parent[u][d] = parent[parent[u][d - 1]][d - 1];

        queue<int> bfs;

        for(int u = 0; u < N; u++)
            if(!deg[u])
                bfs.push(u);

        for(int u, v; !bfs.empty();){
            u = bfs.front(), v = parent[u][0];
            bfs.pop();

            cycle[u] = 0;
            if(!(--deg[v]))
                bfs.push(v);
        }


        for(int u = 0, v, w; u < N; u++){
            if(!cycle[u] || cycle_pos[u] != -1) continue;

            function<void(int)> dfs_cycle = [&](int v) -> void {
                w++;
                cycle_pos[v] = v;

                if(parent[v][0] == u){
                    cycle_length[v] = w, pos[v] = 0;
                    return;
                }

                int x = parent[v][0];
                dfs_cycle(x);

                pos[v] = pos[x] + 1;
                cycle_length[v] = cycle_length[x];
            };

            w = 0;
            pos[u] = 0;
            dfs_cycle(u);
        }

        for(int u = 0; u < N; u++)
            dfs(u);
    }

    void dfs(int u) {
        int v = parent[u][0];
        if(pos[u] != -1 || u == v) return;

        dfs(v);

        cycle_pos[u] = cycle_pos[v];
        pos[u] = pos[v] + 1;
    }

    int kth_parent(int u, int k) {
        for(int d = 0; d < max_depth; d++)
            if((k >> d) & 1)
                u = parent[u][d];
        return u;
    }

    int check(int u, int v, int k) {
        return (k >= 0 && kth_parent(u, k) == v ? k : -1);
    }

    int distance(int u, int v) {
        if(cycle[u] && cycle[v])
            return (pos[u] >= pos[v] ? check(u, v, pos[u] - pos[v]) : check(u, v, cycle_length[u] - (pos[v] - pos[u])));

        if(!cycle[u] && !cycle[v])
            return check(u, v, pos[u] - pos[v]);

        if(cycle[u]) return -1;
        return check(u, v, pos[u] - pos[cycle_pos[u]] + distance(cycle_pos[u], v));
    }
};  

int main(){
 
    FastIO();
    int n, q; cin >> n >> q;
    Graph graph(n);

    for(int u = 0, v; u < n; u++){
        cin >> v, v--;
        graph.add_edge(u, v);
    }

    graph.build();

    for(int i = 0, u, v; i < q; i++){
        cin >> u >> v, u--, v--;
        cout << graph.distance(u, v) << '\n';
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
