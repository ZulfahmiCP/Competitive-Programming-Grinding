#include <bits/stdc++.h>
using namespace std;

#define fi first 
#define se second
#define ll long long
#define pb push_back
#define ppb pop_back 
#define pf push_front
#define ppf pop_front
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define all_range(x) (x).begin(), (x).begin()
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'
#define ttm  template
#define ttp typename

#ifndef ONLINE_JUDGE 
ttm<ttp T> void prd(T x) {cerr << x;}
ttm<ttp T, ttp U> void prd(pair<T, U> x) {cerr << "("; prd(x.fi); cerr<<", "; prd(x.se); cerr<<")";}
ttm<ttp T, ttp ... A> void prd(T x, A... a) {prd(x); cerr << ", "; prd(a...); }
ttm<ttp... A> void debug(A... a) {cerr << "["; prd(a...); cerr <<"]\n";}
ttm<ttp T> void debug(vector<T> c) {cerr <<"[ "; for(auto v : c) {prd(v); cerr << ' ';} cerr << " ]\n";} 
ttm<ttp T> void debug(vector<vector<T>> c) {cerr <<"["; for(auto v : c) debug(v); cerr << '\n';} 
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

#define lc(x) (x << 1)
#define rc(x) (x << 1) | 1

struct node {
    int pref, suff, sum[2];
    bool lz, whole;
    int p, s;

    node() : lz(0), whole(0), pref(-1), suff(-1) {}

    node(int x) {
        sum[x] = 1, sum[!x] = 0;
        pref = suff = 1;
        p = s = x;
        lz = 0, whole = 1;
    }

    void lazy() {
        swap(sum[0], sum[1]);
        p = !p, s = !s;
    }

    void rev() {
        swap(pref, suff);
        swap(p, s);
    }
};

node pull(node a, node b) {
    node c;

    if(a.pref == -1) return b;
    if(b.pref == -1) return a;

    c.pref = a.pref;
    if(a.whole && a.s == b.p) c.pref += b.pref;

    c.suff = b.suff;
    if(b.whole && b.p == a.s) c.suff += a.suff;

    for(int i = 0; i < 2; i++){
        c.sum[i] = max({
            a.sum[i], b.sum[i],
            (a.s == i && b.p == i ? a.suff + b.pref : 0)
        });
    }

    c.p = a.p;
    c.s = b.s;

    if(a.whole && b.whole && a.s == b.p)
        c.whole = 1;

    return c;
}

struct SegTree {
    int N;
    vector<int> arr;
    vector<node> tree;

    SegTree(int n = 0) : N(n), arr(N), tree(4 * N + 5) {}

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = node(arr[l]);
            return;
        } 
        int m = (l + r) >> 1;
        build(lc(x), l, m);
        build(rc(x), m + 1, r);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    void push(int x, int l, int r) {
        if(!tree[x].lz) return;
        tree[x].lazy();
        if(l != r){
            tree[lc(x)].lz ^= 1;
            tree[rc(x)].lz ^= 1;
        }
        tree[x].lz = 0;
    }
    
    void update(int l, int r) { 
        assert(l <= r);
        modify(1, 0, N - 1, l, r); 
    }

    void modify(int x, int l, int r, int ql, int qr) {
        push(x, l, r);
        if(qr < l || r < ql) return;
        if(ql <= l && r <= qr){
            tree[x].lz = 1;
            push(x, l, r);
            return;
        }
        int m = (l + r) >> 1;
        modify(lc(x), l, m, ql, qr);
        modify(rc(x), m + 1, r, ql, qr);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    node calc(int l, int r) {
        assert(l <= r);
        return process(1, 0, N - 1, l, r);
    }

    node process(int x, int l, int r, int ql, int qr) {
        push(x, l, r);
        if(qr < l || r < ql) return node();
        if(ql <= l && r <= qr) return tree[x];
        int m = (l + r) >> 1;
        return pull(process(lc(x), l, m, ql, qr), process(rc(x), m + 1, r, ql, qr));
    }
};

struct HLD {
    int N, cnt = 0;
    vector<vector<int>> adj;
    vector<int> val, pos, head, dep, sub, par;
    SegTree seg;

    HLD(int n) : N(n), adj(N), sub(N, 1), pos(N), head(N), dep(N, 0), val(N), par(N), seg(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build() {
        dep[0] = par[0] = 0;
        dfs_sub(0);
        dfs_hld(0, 0);
        seg.build(1, 0, N - 1);
    }

    int dfs_sub(int u) {
        eliminate(adj[u], par[u]);
        for(int &v : adj[u]){
            dep[v] = dep[u] + 1;
            par[v] = u, sub[u] += dfs_sub(v);
        }
        sort(all(adj[u]), [&](int a, int b) {
            return sub[a] > sub[b];
        });
        return sub[u];
    }

    void dfs_hld(int u, bool heavy) {
        seg.arr[pos[u] = cnt++] = val[u];
        head[u] = heavy ? head[par[u]] : u;
        bool heavy_child = 1;

        for(int &v : adj[u]){
            dfs_hld(v, heavy_child);
            heavy_child = 0;
        }
    }

    void update_path(int u, int v) {
        for(; head[u] != head[v]; v = par[head[v]]) {
            if(dep[head[u]] > dep[head[v]])
                swap(u, v);
            seg.update(pos[head[v]], pos[v]);
        }
        if(dep[u] > dep[v]) swap(u, v);
        seg.update(pos[u], pos[v]);
    } 

    int calc_path(int u, int v) {
        node x, y;

        for(; head[u] != head[v];){
            if(dep[head[u]] > dep[head[v]]){
                x = pull(seg.calc(pos[head[u]], pos[u]), x);
                u = par[head[u]];
            } else {
                y = pull(seg.calc(pos[head[v]], pos[v]), y);
                v = par[head[v]];
            }
        }

        if(dep[u] < dep[v]){
            y = pull(seg.calc(pos[u], pos[v]), y);
        } else {
            x = pull(seg.calc(pos[v], pos[u]), x);
        }

        x.rev();
        x = pull(x, y);
        return max(x.sum[0], x.sum[1]);
    }
};

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n,q; cin >> n >> q;
    string s; cin >> s;
    HLD tree(n);

    for(int i = 0; i < n; i++)
        tree.val[i] = s[i] == 'W';

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.build();

    for(int i = 0, t,l,r; i < q; i++){
        cin >> t >> l >> r, l--, r--;

        if(t == 1){
            tree.update_path(l, r);
        } else {
            cout << tree.calc_path(l, r) << endl;
        }
    }
    
    return 0;
}