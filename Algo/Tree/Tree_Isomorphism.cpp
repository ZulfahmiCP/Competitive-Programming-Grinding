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

struct Tree { 
    int N;
    vector<vector<int>> adj, layer;
    vector<int> par;

    Tree(int n) : N(n), adj(N) { }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> center() {
        int u = 0;

        for(int k = 0; k < 2; k++){ 
            queue<int> bfs;
            par.assign(N, -1);
            bfs.push(par[u] = u); 

            while(!bfs.empty()){
                u = bfs.front(); 
                bfs.pop();

                for(const int &v: adj[u]) {
                    if(par[v] != -1) continue;
                    bfs.push(v);
                    par[v] = u;
                }
            }
        }

        vector<int> path = {u}; 
        while (u != par[u]) 
            path.pb(u = par[u]);

        int m = sz(path); 
        return (m & 1 ? vector<int>{path[m / 2]} : 
                        vector<int>{path[m / 2 - 1], path[m / 2]});
    }

    int split(int node) { 
        par.assign(N, -1); 
        par[node] = N;
        layer = {{node}};

        while(true){
            vector<int> children;
            for(const int &u : layer.back()){
                for(const int &v : adj[u]){
                    if(par[v] != -1) 
                        continue;
                    par[v] = u;
                    children.pb(v);
                }
            }

            if(children.empty()) 
                break;
            layer.pb(children);
        }

        return sz(layer);
    }
};

bool isomorphic(Tree &S, int s, Tree &T, int t) {
    if(S.N != T.N || S.split(s) != T.split(t)) 
        return 0;
    
    vector<vector<int>> A(S.N + 1), B(T.N + 1);
    vector<int> a(S.N), b(T.N);

    for(int h = S.layer.size() - 1, index; h >= 0; h--){
        map<vector<int>, int> M;

        for(const int &u : S.layer[h]){
            sort(all(A[u]));
            M[A[u]] = 0;
        }

        for(const int &u : T.layer[h]){
            sort(all(B[u]));
            M[B[u]] = 0;
        }

        index = 0;
        for(auto &p : M) 
            p.se = index++;

        for(const int &u : S.layer[h]){
            a[u] = M[A[u]];
            A[S.par[u]].pb(a[u]);
        }

        for(const int &u : T.layer[h]){
            b[u] = M[B[u]];
            B[T.par[u]].pb(b[u]);
        }
    }

    return a[s] == b[t];
}
bool isomorphic(Tree &S, Tree &T) {
    auto x = S.center(), y = T.center();
    if(sz(x) != sz(y))
        return 0;
    if(isomorphic(S, x[0], T, y[0])) 
        return 1;
    return sz(x) > 1 && isomorphic(S, x[1], T, y[0]);
}

int main(){
 
    FastIO();
    int t,n; cin >> t;
    while(t--){
        cin >> n;
        Tree S(n), T(n);

        for(int i = 1, u, v; i < n; i++){
            cin >> u >> v, u--, v--;
            S.add_edge(u, v);
        }

        for(int i = 1, u, v; i < n; i++){
            cin >> u >> v, u--, v--;
            T.add_edge(u, v);
        }

        cout << (isomorphic(S, T) ? "YES" : "NO") << '\n';
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
