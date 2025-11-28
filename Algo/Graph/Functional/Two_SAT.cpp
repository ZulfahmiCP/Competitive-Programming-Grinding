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

/*  Types of Constrains
    (x OR y) = (~x ==> y) AND (~y ==> x)

    1. If we want force x to be true, then add (x OR x)
    2. If we one condition must be true, the add (x OR y) AND (~x OR ~y)
    3. If at least one condition must be true, then add (x OR y)
    4. If both condition must be true, then add (~x OR y) AND (x OR ~y) 

    clause OR ==> At least one of them is true
    clause XOR ==> Only one of them is true
    clause AND ==> Both of them have the same value
*/

struct TwoSAT {
    int N;
    vector<vector<int>> adj, rev_adj;
    vector<int> comp, order, ans;
    vector<bool> vis;

    TwoSAT(int n = 0) : N(n), adj(2 * N), rev_adj(2 * N),
                        comp(2 * N), vis(2 * N), ans(2 * N) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    void add_clause_or(int u, bool a, int v, bool b) {
        add_edge(u + (a ? N : 0), v + (b ? 0 : N));
        add_edge(v + (b ? N : 0), u + (a ? 0 : N));
    }

    void add_clause_xor(int u, bool a, int v, bool b) {
        add_clause_or(u, a, v, b);
        add_clause_or(u, !a, v, !b);
    }

    void add_clause_and(int u, bool a, int v, bool b) {
        add_clause_xor(u, !a, v, b);
    }

    void dfs(int u) {
        vis[u] = 1;
        for(const int &v : adj[u])
            if(!vis[v]) dfs(v);
        order.pb(u);
    }

    void scc(int u, int i) {
        vis[u] = true;
        comp[u] = i;

        for(const int &v : rev_adj[u])
            if(!vis[v]) scc(v, i);
    }

    bool satisfiable() {
        fill(all(vis), 0);

        for(int u = 0; u < 2 * N; u++)
            if(!vis[u]) dfs(u);

        fill(all(vis), 0);
        reverse(all(order));

        int id = 0;
        for(const int &v : order)
            if(!vis[v]) scc(v, id++);

        for(int u = 0; u < N; u++){
            if(comp[u] == comp[u + N])
                return 0;
            ans[u] = (comp[u] > comp[u + N]);
        }

        return 1;
    }
};

int main(){
 
    FastIO();
    int n,d; cin >> n >> d;
    vector<int> A(n), B(n);
    TwoSAT graph(n);

    for(int i = 0; i < n; i++)
        cin >> A[i] >> B[i];

    for(int u = 0; u < n; u++){
        for(int v = u + 1; v < n; v++){
            if(abs(A[u] - A[v]) < d)
                graph.add_clause_or(u, 0, v, 0);
            if(abs(A[u] - B[v]) < d)
                graph.add_clause_or(u, 0, v, 1);
            if(abs(B[u] - A[v]) < d)
                graph.add_clause_or(u, 1, v, 0);
            if(abs(B[u] - B[v]) < d)
                graph.add_clause_or(u, 1, v, 1);
        }
    }

    if(graph.satisfiable()){
        cout << "Yes\n";
        for(int u = 0; u < n; u++)
            cout << (graph.ans[u] ? A[u] : B[u]) << '\n';
    } else 
        cout << "No\n";

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
