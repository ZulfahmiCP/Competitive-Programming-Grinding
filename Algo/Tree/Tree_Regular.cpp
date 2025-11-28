#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>

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
template<typename T, typename U>void prd(const pair<T, U>& value);
template<typename T, typename... Args>void prd(const T& value, Args... args);
template<typename... Args>void debug(Args... args);
template<typename K, typename V>void debug(const map<K, V>& c);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Tree {
    int N, root, diameter;
    vector<vector<int>> adj;
    vector<int> tour, in, out;
    vector<int> sub, depth, parent;

    Tree(int n) : N(n), in(N), out(N), adj(N),
                  sub(N, 1), depth(N), parent(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build(int rt = 0) {
        root = rt;  
        depth[root] = 0;
        parent[root] = -1;
        dfs_sub(root);
    }

    int dfs_sub(int u) {
        in[u] = sz(tour);
        tour.pb(u);

        for(const int &v : adj[u]){
            eliminate(adj[v], u);
            parent[v] = u, depth[v] = depth[u] + 1;
            sub[u] += dfs_sub(v);
        }

        out[u] = sz(tour);
        tour.pb(u);

        return sub[u];
    }

    bool is_anc(int u, int v) {
        return in[u] < in[v] && out[u] > out[v];
    }

    int find_diameter() {
        for(int u = 1; u < N; u++)
            if(depth[diameter] < depth[u])
                diameter = u;
        
        vector<int> d(N, 0);

        function<void(int, int)> explore = [&](int u, int p) -> void {
            for(const int &v : adj[u]) if(v != p) {
                d[v] = d[u] + 1;
                explore(v, u);
            }
        };

        explore(diameter, -1);

        for(int u = 1; u < N; u++)
            if(d[diameter] < d[u])  
                diameter = u;
        
        diameter = depth[diameter];
        return diameter;
    }

    int center() {
        vector<int> deg(N, 0);
        queue<int> leaves;

        for(int u = 0; u < N; u++){
            deg[u] = sz(adj[u]);
            if(deg[u] == 1)
                leaves.push(u);
        }

        for(int u; sz(leaves) > 1;){
            u = leaves.front();
            leaves.pop();

            for(const int &v : adj[u])
                if((--deg[v]) == 1)
                    leaves.push(v);
        }

        return leaves.front();
    }
};

struct Treet {
    int N, root;
    vector<vector<pair<int, int>>> adj;
    vector<int> tour, in, out, weight;
    vector<int> sub, depth, parent;

    Treet(int n) : N(n), in(N), out(N), adj(N), depth(N),
                  sub(N, 1), parent(N), weight(N, 0) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    void build(int rt = 0) {
        root = rt;  
        depth[root] = 0;
        parent[root] = -1;
        dfs_sub(root);
    }

    int dfs_sub(int u) {
        in[u] = sz(tour);
        tour.pb(u);

        for(const auto &[v, w] : adj[u]){
            eliminate(adj[v], make_pair(u, w));
            parent[v] = u, depth[v] = depth[u] + 1;
            sub[u] += dfs_sub(v);
            weight[u] += w + weight[v];
        }

        out[u] = sz(tour);
        tour.pb(u);

        return sub[u];
    }

    bool is_anc(int u, int v) {
        return in[u] < in[v] && out[u] > out[v];
    }
};

int main(){
 
    FastIO();
    int t,n; cin >> t;
    while(t--){
        cin >> n;
        Tree tree(n);

        for(int i = 1, u, v; i < n; i++){
            cin >> u >> v, u--, v--;
            tree.add_edge(u, v);
        }


    }

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& value){cerr<<"(";prd(value.first);cerr<<", ";prd(value.second);cerr<<")";}
template<typename T, typename... Args>void prd(const T& value, Args... args){prd(value);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr << "]\n";}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c) { for (const auto &v : c) debug(v); cerr << '\n';}