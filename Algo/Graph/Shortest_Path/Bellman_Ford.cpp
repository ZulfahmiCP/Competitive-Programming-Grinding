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

struct BellmanFord {
    int N;
    vector<vector<pair<int, int>>> graph; 
    vector<int> par, cycle;
    vector<ll> dist; 

    BellmanFord(int n) : N(n), graph(n), par(N, -1), dist(n, INFL) {}

    void add_edge(int u, int v, int w) {
        graph[u].pb({v, w});
    }

    bool solve(int source) {
        dist[source] = 0;

        int x;
        for(int i = 1; i < N; i++){ x = -1;
            for(int u = 0; u < N; u++) if(dist[u] != INFL)
                for(const auto &[v, w] : graph[u])  
                    if(dist[u] + w < dist[v])
                        dist[v] = dist[u] + w, par[v] = u;
        }

        if(x == -1) return 1;

        for(int i = 0; i < N; i++) x = par[x];

        for(int v = x;;v = par[v]){
            cycle.pb(v);
            if(v == x && sz(cycle) > 1)
                break;
        }

        reverse(all(cycle));

        return 0;
    }
};

struct Edge {
    int u, v, w;
};

struct BellmanFord {
    int N;
    vector<Edge> edges;
    vector<int> par, cycle;
    vector<ll> dist;

    BellmanFord(int n) : N(n), dist(N, INFL), par(N, -1) {}

    void add_edge(int u, int v, int w) {
        edges.pb({u, v, w});
    }w

    bool solve(int source) {
        dist[source] = 0;

        int x;
        for(int i = 0; i < N; i++){ x = -1;
            for(const auto &[u, v, w] : edges)
                if(dist[u] != INFL && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w, par[v] = u, x = v;
        }

        if(x == -1)
            return 1;

        for(int i = 0; i < N; i++)
            x = par[x];

        for(int v = x;;v = par[v]){
            cycle.pb(v);
            if(v == x && sz(cycle) > 1)
                break;
        }

        reverse(all(cycle));

        return 0;
    }
};

int main(){
 
    FastIO();
    

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
