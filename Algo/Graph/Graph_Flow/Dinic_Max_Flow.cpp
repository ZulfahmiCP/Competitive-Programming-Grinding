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

struct Dinic {
    struct Edge {
        ll v, cap, flow, rev;
        Edge(int t, int c, int r) : v(t), cap(c), flow(0), rev(r) {}
    };

    int N;
    vector<vector<Edge>> graph;
    vector<int> level, start;

    Dinic(int n) : N(n), graph(n), level(n), start(n) {}

    void add_edge(int u, int v, int c) {
        graph[u].pb(Edge(v, c, sz(graph[v])));
        graph[v].pb(Edge(u, 0, sz(graph[u]) - 1));
    }

    bool bfs(int s, int t) {
        fill(all(level), -1);
        level[s] = 0;

        queue<int> q;
        q.push(s);

       for(int u; !q.empty();) {
            u = q.front();
            q.pop();

            for(auto &[v, cap, flow, rev] : graph[u]) {
                if(level[v] == -1 && flow < cap){
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }

        return level[t] != -1;
    }

    int dfs(int u, int t, int flow) {
        if(u == t) return flow;

        for(auto &[v, cap, flow, rev] : graph[u]){
            if(level[v] == level[u] + 1 && flow < cap){
                int path_flow = dfs(v, t, min(flow, cap - flow));

                if(path_flow <= 0) 
                    continue;

                flow += path_flow;
                graph[v][rev].flow -= path_flow;
                
                return path_flow;
            }
        }

        return 0;
    }

    int max_flow(int s, int t) {
        int max_flow = 0;

        while(bfs(s, t)){
            fill(all(start), 0);
            while(int path_flow = dfs(s, t, INF))
                max_flow += path_flow;
        }

        return max_flow;
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    Dinic graph(n);

    for(int i = 0, u, v, c; i < m; i++){
        cin >> u >> v >> c, u--, v--;
        graph.add_edge(u, v, c);
    }

    cout << graph.max_flow(0, n - 1) << '\n';

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
