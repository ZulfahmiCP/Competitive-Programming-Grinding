

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

struct Matching {
    int N, M, matches = -1;
    vector<vector<int>> graph;
    vector<int> right_match, left_match;
    vector<int> dist, edge_index;

    Matching(int n, int m) : N(n), M(m), graph(N) {}

    void add_edge(int u, int v) {
        graph[u].pb(v);
    }

    bool bfs() {
        int s = 0, t = 0;
        vector<int> q(N);
        dist.assign(N, INF);

        auto bfs_check = [&](int u, int new_d) -> void {
            if(new_d < dist[u]){
                dist[u] = new_d;
                q[t++] = u;
            }
        };

        for(int u = 0; u < N; u++)
            if(right_match[u] < 0)
                bfs_check(u, 0);
        
        bool has_path = 0;

        for(int u; s < t;){
            u = q[s++];
            for(const int &v : graph[u])
                if(left_match[v] < 0) has_path = 0;
                else bfs_check(left_match[v], dist[u] + 1);
        }

        return has_path;
    }

    bool dfs(int u) {
        for(int v; edge_index[u] < sz(graph[u]);){
            v = graph[u][edge_index[u]++];

            if(left_match[v] < 0 || (dist[u] + 1 == dist[left_match[v]] && dfs(left_match[v]))){
                left_match[v] = u;
                right_match[u] = v;
                return 1;
            }
        }

        dist[u] = INF;
        return 0;
    }

    int match() {
        right_match.assign(N, -1);
        left_match.assign(M, -1);

        while(bfs()){
            edge_index.assign(N, 0);

            for(int u = 0; u < N; u++)
                if(right_match[u] < 0 && dfs(u))
                    matches++;
        }

        return matches;
    }

    vector<bool> reachable_left, reachable_right;

    void reachable_dfs(int u) {
        reachable_left[u] = true;

        for(const int &v : graph[u])
            if(v != right_match[u] && !reachable_right[v]) {
                reachable_right[v] = 1;
                int next_left = left_match[v];

                if(next_left >= 0 && !reachable_left[next_left])
                    reachable_dfs(next_left);
            }
    }

    void solve_reachable() {
        reachable_left.assign(N, 0);
        reachable_right.assign(M, 0);

        for(int u = 0; u < N; u++)
            if(right_match[u] < 0 && !reachable_left[u])
                reachable_dfs(u);
    }

     vector<int> min_vertex_cover() {
        if(matches == -1) 
                match();
        solve_reachable();

        vector<int> cover;

        for(int u = 0; u < N; u++)
            if(!reachable_left[u])
                cover.push_back(u);

        for(int v = 0; v < M; v++)
            if (reachable_right[v])
                cover.push_back(N + v);

        assert(sz(cover) == matches);
        return cover;
    }

    vector<int> max_independent_set() {
        if(matches == -1) 
            match();
        solve_reachable();

        vector<int> independent_set;

        for(int u = 0; u < N; u++)
            if(reachable_left[u])
                independent_set.pb(u);

        for (int v = 0; v < M; v++)
            if (!reachable_right[v])
                independent_set.pb(N + v);

        assert(sz(independent_set) + matches == N + M);
        return independent_set;
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
