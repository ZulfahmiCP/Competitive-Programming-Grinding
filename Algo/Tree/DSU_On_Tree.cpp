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
    struct Node {
        ll mx, ans; 
        map<ll, ll> cnt;

        void merge(Node &a) {
            if(sz(cnt) < sz(a.cnt)){
                swap(cnt, a.cnt);
                mx = a.mx;
                ans = a.ans;
            }

            for(auto &[col, occ] : a.cnt){
                cnt[col] += occ;
                if(cnt[col] > mx){
                    mx = cnt[col];
                    ans = col;
                } else if(cnt[col] == mx)
                    ans += col;
            }

            a.cnt.clear();
        }
    };
    int N, root;
    vector<vector<int>> adj;
    vector<int> tour, in, out;
    vector<int> sub, depth, parent;
    vector<Node> node;


    Tree(int n) : N(n), in(N), out(N), adj(N), node(N),
                  sub(N, 1), depth(N), parent(N) {}

    void build(int rt = 0) {
        root = rt;  
        depth[root] = 0;
        parent[root] = -1;
        dfs_sub(root);
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int dfs_sub(int u) {
        in[u] = sz(tour);
        tour.pb(u);

        for(const int &v : adj[u]){
            eliminate(adj[v], u);
            parent[v] = u, depth[v] = depth[u] + 1;
            sub[u] += dfs_sub(v);
            node[u].merge(node[v]);
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
    int n; cin >> n;
    Tree tree(n);

    for(int u = 0, c; u < n; u++){
        cin >> c;
        tree.node[u] = {1, c};
        tree.node[u].cnt[c]++;
    }
    
    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.build();
    for(int u = 0; u < n; u++)
        cout << tree.node[u].ans << " \n"[u == n - 1];

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
