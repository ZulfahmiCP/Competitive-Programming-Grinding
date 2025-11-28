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

#define lc(x) (x << 1)
#define rc(x) (x << 1) | 1

struct SegTree {
    struct node {
        ll sum = 0, lz = 0;
    };

    int N;
    vector<int> arr;
    vector<node> tree;

    SegTree(int n) : N(n), arr(N), tree(4 * N) {}

    node pull(node a, node b) {
        return {
            a.sum + b.sum
        };
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x].sum = arr[l];
            return;
        }

        int m = (l + r) >> 1;

        build(lc(x), l, m);
        build(rc(x), m + 1, r);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    void push(int x, int l, int r) {
        if(!tree[x].lz)
            return;

        tree[x].sum += tree[x].lz * (r - l + 1);

        if(l != r){
            tree[lc(x)].lz += tree[x].lz;
            tree[rc(x)].lz += tree[x].lz;
        }

        tree[x].lz = 0;
    }

    void update(int l, int r, ll v) {
        modify(1, 0, N - 1, l, r, v);
    }

    void modify(int x, int l, int r, int ql, int qr, ll v) {
        push(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            tree[x].lz = v;
            push(x, l, r);
            return;
        }

        int m = (l + r) >> 1;

        modify(lc(x), l, m, ql, qr, v);
        modify(rc(x), m + 1, r, ql, qr, v);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    ll calc(int l, int r) {
        return process(1, 0, N - 1, l, r).sum;
    }

    node process(int x, int l, int r, int ql, int qr) {
        push(x, l, r);

        if(l > qr || ql > r)
            return node();

        if(ql <= l && r <= qr)
            return tree[x];

        int m = (l + r) >> 1;

        return pull(process(lc(x), l, m, ql, qr),   
                    process(rc(x), m + 1, r, ql, qr));
    }
};

struct HLD {
    int N, cnt;
    vector<vector<pair<int, int>>> adj; 
    vector<int> dep, sub, par;
    vector<int> pos, head;
    SegTree seg;
 
    HLD(int n) : N(n), cnt(0), adj(N), pos(N), head(N),
                 sub(N, 1), dep(N), par(N), seg(N) {}
 
    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
 
    void build(int root = 0) {
        dep[root] = par[root] = 0;
        seg.arr[pos[root] = cnt++] = 0;
        dfs_sub(root); 
        dfs_hld(root, 0);
        seg.build(1, 0, N - 1);
    }
 
    int dfs_sub(int u) {
        for(auto &[v, w] : adj[u]){
            eliminate(adj[v], make_pair(u, w));
            dep[v] = dep[u] + 1;
            par[v] = u;
            sub[u] += dfs_sub(v);
        }

        sort(all(adj[u]), [&](pair<int, int> &a, pair<int, int>&b) {
            return sub[a.fi] > sub[b.fi];
        });

        return sub[u];
    }
 
    void dfs_hld(int u, bool heavy) {
        head[u] = heavy ? head[par[u]] : u;
        bool heavy_child = 1;

        for(auto &[v, w] : adj[u]){
            seg.arr[pos[v] = cnt++] = w;
            dfs_hld(v, heavy_child);
            heavy_child = 0;
        }
    }
 
    ll calc_path(int u, int v) {
        ll res = 0;

        for(;head[u] != head[v]; u = par[head[u]]){
            if(dep[head[u]] < dep[head[v]])
                swap(u, v);
            res += seg.calc(pos[head[u]], pos[u]);
        }
 
        if(dep[u] > dep[v])
            swap(u, v);
            
        res += seg.calc(pos[u] + 1, pos[v]);
        return res;
    }
    
    void update_path(int u, int v, int x) {
        for (; head[u] != head[v]; v = par[head[v]]) {
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            seg.update(pos[head[v]], pos[v], x);
        }
        if (dep[u] > dep[v]) swap(u, v);
        if (u != v) seg.update(pos[u] + 1, pos[v], x);
    }

    ll calc_subtree(int u) {
        if (sub[u] == 1) return 0;
        return seg.calc(pos[u] + 1, pos[u] + sub[u] - 1);
    }
    
    void update_subtree(int u, int x) {
        if (sub[u] == 1) return;
        seg.update(pos[u] + 1, pos[u] + sub[u] - 1, x);
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
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
