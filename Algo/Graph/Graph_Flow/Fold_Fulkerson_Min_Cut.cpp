

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

struct MinCut {
    int N;
    vector<pair<int, int>> cut_edges;
    vector<vector<int>> cap, graph;
    vector<int> parent;
    vector<bool> vis;

    MinCut(int n) : N(n), graph(N), vis(N, 0), parent(N), cap(N, vector<int>(N, 0)) {};

    void add_edge(int u, int v) {
        graph[u].pb(v); cap[u][v]++;
        graph[v].pb(u); cap[v][u]++;
    }

    int bfs(int s, int t) {
        fill(all(parent), -1);

        queue<pair<int, int>> explore;
        explore.push({s, INF});
        parent[s] = s;

        for(int new_flow; !explore.empty();){
            auto &[u, flow] = explore.front();
            explore.pop();

            for(const int &v : graph[u]){
                if(parent[v] != -1 || !cap[u][v])
                    continue;
                
                parent[v] = u;
                new_flow = min(flow, cap[u][v]);
                if(v == t) return new_flow;
                explore.push({v, new_flow});
            }
        }

        return 0;
    }

    int max_flow(int s, int t) {
        int flow = 0, new_flow;

        while(new_flow = bfs(s, t)){
            flow += new_flow;
            for(int u = t; u != s; u = parent[u]){
                cap[parent[u]][u] -= new_flow;
                cap[u][parent[u]] += new_flow;
            }
        }

        return flow;
    }

    void dfs(int u) {
        vis[u] = 1;
        for(const int &v : graph[u])
            if(!vis[v] && cap[u][v])
                dfs(v);
    }

    int min_cut(int s, int t) {
        int cut = max_flow(s, t);
        dfs(s);

        for(int u = 0; u < N; u++){
            if(!vis[u]) continue;
            for(const int &v : graph[u])
                if(!vis[v]) 
                    cut_edges.pb({u, v});
        }

        return cut;
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    MinCut graph(n);

    for(int i = 0, u, v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }
    
    cout << graph.min_cut(0, n - 1) << '\n';
    for(auto &[u, v] : graph.cut_edges)
        cout << u + 1 << ' ' << v + 1 << '\n';

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
