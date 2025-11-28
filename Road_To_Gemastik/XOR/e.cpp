#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define uniq(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'
#define ttm template
#define ttp typename

using namespace std;
ttm<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}

ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cm = 1;}cerr<<"]\n";}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

struct SegTree {
    struct node {
        int sum = 0;
        int lz = 0;
    };
    int N;
    vector<node> tree;

    SegTree(int n = 0) : N(n), tree(4 * N) {}
    
    #define lc(x) (x << 1)
    #define rc(x) (x << 1) | 1

    void push(int x, int l, int r) {
        if(!tree[x].lz) return;
        if((r - l + 1) & 1) tree[x].sum ^= tree[x].lz;
        if(l != r){
            tree[lc(x)].lz ^= tree[x].lz;
            tree[rc(x)].lz ^= tree[x].lz;
        }
        tree[x].lz = 0;
    }

     void update(int l, int r, int x) {
        modify(1, 0, N - 1, l, r, x);
    }

    void modify(int x, int l, int r, int ql, int qr, int v) {
        push(x, l, r);

        if(qr < l || r < ql) return;
        
        if(ql <= l && r <= qr){
            tree[x].lz = v;
            push(x, l, r);
            return;
        }

        int m = (l + r) >> 1;

        modify(lc(x), l, m, ql, qr, v);
        modify(rc(x), m + 1, r, ql, qr, v);

        tree[x].sum = tree[lc(x)].sum ^ tree[rc(x)].sum;
    }

    int calc(int j) {
        return process(1, 0, N - 1, j);
    }

    int process(int x, int l, int r, int j) {
        push(x, l, r);
        if(l == r) return tree[x].sum;
        int m = (l + r) >> 1;
        return j <= m ? process(lc(x), l, m, j) : process(rc(x), m + 1, r, j);
    }
};

struct Tree {
    int N;
    vector<vector<int>> adj;
    vector<int> val, in, out, tour, dep;
    SegTree seg[2];

    Tree(int n) : N(n), val(N, 0), adj(N), in(N), out(N), dep(N, 0) {
        seg[0] = SegTree(N);
        seg[1] = SegTree(N);
    }
    
    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build() {
        dfs(0, -1);
    }

    void dfs(int u, int p) {
        in[u] = sz(tour);
        tour.pb(u);

        for(int &v : adj[u]){
            if(v == p) continue;
            dep[v] = dep[u] ^ 1;
            dfs(v, u);
        }
        
        out[u] = sz(tour) - 1;
    }

    void update(int u, int x) {
        seg[dep[u]].update(in[u], out[u], x);
    }

    int calc(int u) {
        return seg[dep[u]].calc(in[u]);
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    Tree tree(n);

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.build(); 

    int q; cin >> q;

    for(int i = 0, t,u,x; i < q; i++){
        cin >> t;

        if(t == 1){
            cin >> u >> x, u--;
            tree.update(u, x);
        } else {
            cin >> u, u--;
            cout << tree.calc(u) << endl;
        }
    }
    
    return 0;
}

