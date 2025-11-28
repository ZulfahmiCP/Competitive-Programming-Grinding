#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long 
#define pb push_back
#define ppb pop_back
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'

const ll INFL = 2e18 + 7;

struct SegTree {
    struct node {
        ll mn;
        int l, r, lc, rc;
        node(int L, int R) : mn(INFL), l(L), r(R), lc(-1), rc(-1) {}
    };
    int N;
    vector<node> tree;

    SegTree() {}
    SegTree(int n) : N(n) {
        tree.pb(node(0, N - 1));
    }

    void new_node(int x) {
        if(tree[x].l == tree[x].r) return;
        int m = (tree[x].l + tree[x].r) >> 1;
        if(tree[x].lc == -1){
            tree[x].lc = sz(tree);
            tree.pb(node(tree[x].l, m));
        }
        if(tree[x].rc == -1){
            tree[x].rc = sz(tree);
            tree.pb(node(m + 1, tree[x].r));
        }
    }

    void update(int j, ll v) {
        modify(0, j, v);
    }

    void modify(int x, int j, ll v) {
        if(tree[x].l == tree[x].r){
            tree[x].mn = v;
            return;
        }

        int m = (tree[x].l + tree[x].r) >> 1;
        new_node(x);
        j <= m ? modify(tree[x].lc, j, v) : modify(tree[x].rc, j, v);
        tree[x].mn = min(tree[tree[x].lc].mn, tree[tree[x].rc].mn);
    }

    ll calc(int l, int r) {
        return process(0, l, r);
    }

    ll process(int x, int l, int r) {
        if(x == -1 || r < tree[x].l || tree[x].r < l) return INFL;
        if(l <= tree[x].l && tree[x].r <= r) return tree[x].mn;
        int m = (tree[x].l + tree[x].r) >> 1;
        return min(process(tree[x].lc, l, r), process(tree[x].rc, l, r));
    }
};

struct Tree {
    int N, Q;
    vector<vector<pair<int, int>>> adj;
    vector<vector<array<int, 3>>> query;
    vector<ll> ans, dist, idx;
    vector<vector<int>> leaf;
    vector<SegTree> seg;

    Tree(int n, int q) : N(n), Q(0), adj(N), query(N), seg(N), ans(q, -1), idx(N), leaf(N), dist(N, 0) {
        for(int i = 0; i < N; i++){
            seg[i] = SegTree(N);
            idx[i] = i;
        }
    }

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
    }

    void add_query(int u, int l, int r) {
        query[u].pb({l, r, Q++});
    }    

    void solve() {
        dfs(0);
    }

    void dfs(int u) {
        if(sz(adj[u]) == 0){
            seg[u].update(u, dist[u]);
            leaf[u].pb(u);
            return;
        }

        for(auto &[v, w] : adj[u]){
            dist[v] = dist[u] + w;
            dfs(v);

            if(sz(leaf[u]) < sz(leaf[v])){
                swap(leaf[u], leaf[v]);
                swap(idx[u], idx[v]);
            }

            for(int &l : leaf[v]){
                seg[idx[u]].update(l, dist[l]);
                leaf[u].pb(l);
            }
        }

        for(auto &[l, r, i] : query[u]){
            ll res = seg[idx[u]].calc(l, r);
            if(res != INFL) ans[i] = res - dist[u];
        }
    }   
};

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    Tree tree(n, q);

    for(int u = 1, p, w; u < n; u++){
        cin >> p >> w, p--;
        tree.add_edge(p, u, w);
    }

    for(int i = 0, u,l,r; i < q; i++){
        cin >> u >> l >> r;
        u--, l--, r--;
        tree.add_query(u, l, r);
    }

    tree.solve();
    for(int i = 0; i < q; i++) cout << tree.ans[i] << endl;

    return 0;
}
