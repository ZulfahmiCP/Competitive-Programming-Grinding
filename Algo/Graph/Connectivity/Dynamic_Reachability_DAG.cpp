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
#define make_unique(x) (x).erase(unique(all(x)), (x).end());
#define all_range(x) sort(all(x)), (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void prd(const T& x);
template <typename T, typename U>
    void prd(const pair<T, U>& value);
template <typename T, typename... Args>
    void prd(const T& value, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& cont);
template <typename T>
    void debug(const set<T>& cont);
template <typename T>
    void debug(const vector<T>& cont);
template <typename T>
    void debug(const vector<vector<T>> &cont);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

// 
// Italiano's dynamic Reachability data structure for DAG
//
// Description:
//   It is a data structure that admits the following operations:
//     add_edge(s, t):     insert edge (s,t) to the network if
//                         it does not make a cycle
//
//     is_reachable(s, t): return true iff there is a path s --> t
//
// Algorithm:
//   We maintain Reachability trees T(u) for all u in V.
//   Then is_reachable(s, t) is solved by checking "t in T(u)".
//   For add_edge(s, t), if is_reachable(s, t) or is_reachable(t, s) then
//   no update is performed. Otherwise, we dfs T(s) and T(t).
//
// Complexity:
//   amortized O(n) per update
//
// Verified:
//   SPOJ 9458: Ghosts having fun
//
// References:
//   Giuseppe F. Italiano (1988):
//   Finding paths and deleting edges in directed acyclic graphs.
//   Information Processing Letters, vol. 28, no. 1, pp. 5--11.
//   

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

struct Reachability{
    int N;
    vector<vector<int>> parent;
    vector<vector<vector<int>>> child;

    Reachability(int n) : N(n), parent(n, vector<int>(N, -1)), 
                          child(N, vector<vector<int>>(N)) { }

    bool is_reachable(int u, int v) {
        return u == v || parent[u][v] >= 0;
    }

    bool add_edge(int u, int v) {
        if(is_reachable(v, u)) 
            return false; // break DAG condition
        if(is_reachable(u, v)) 
            return true;  // no-modification performed

        for(int p = 0; p < N; p++) 
            if(is_reachable(p, u) && !is_reachable(p, v)) 
                dfs(p, v, u, v);
                
        return true;
    }

    void dfs(int root, int sub, int u, int v) {
        parent[root][v] = u;
        child[root][u].pb(v);

        for(const int &c: child[sub][v]) 
            if(!is_reachable(root, c)) 
                dfs(root, sub, v, c);
    }
};

struct Reachability {
    int N;
    vector<vector<int>> adj;
    vector<bool> vis;

    Reachability(int n) : N(n), adj(N), vis(N) { }

    bool is_reachable(int s, int t) {
        fill(all(vis), 0);

        function<bool(int)> visit = [&](int u) -> bool {
            vis[u] = true;
            if(u == t) 
                return true;

            for(const int &v : adj[u]) 
                if(!vis[v] && visit(v)) 
                    return true;
          return false;
        };

        return visit(s);
    }

    bool add_edge(int u, int v) {
        if(is_reachable(v, u)) 
            return false; // break DAG condition
        if(is_reachable(u, v)) 
            return true;  // no-modification performed
            
        adj[u].pb(v);
        return true;
    }
};

int main(){
 
    FastIO();
    int t,n; cin >> t;
    while(t--){
        cin >> n;
        vector<int> A(n);

        for(int &a : A)
            cin >> a;
    }

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& value){ cerr << "("; prd(value.first); cerr << ", "; prd(value.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& value, Args... args){prd(value); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
